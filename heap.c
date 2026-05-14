#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

Fila *criarFila(int n, int (*comparaElementos)(void*, void*)){
    Fila* fila = malloc(sizeof(Fila));
    fila->tamanhoTotal = n;
    fila->tamanhoAtual = 0;
    fila->elementos = malloc(n*sizeof(void*));
    fila->comparar = comparaElementos;
    return fila;
}
void inserirFila(Fila* fila, void* novoElemento){
    if (fila->tamanhoTotal == fila->tamanhoAtual){
        printf("fila cheia");
        return;
    }
    fila->elementos[fila->tamanhoAtual] = novoElemento;
    fila->tamanhoAtual++;
    subirElemento(fila, fila->tamanhoAtual - 1);
}
void subirElemento(Fila* fila, int i){
    while(i > 0 && fila->comparar(fila->elementos[i], fila->elementos[(i-1)/2])){
        void* temp = fila->elementos[(i-1)/2];
        fila->elementos[(i-1)/2] = fila->elementos[i];
        fila->elementos[i] = temp;
        i = (i-1)/2;
    }
}
void* removerFila(Fila* fila){
    if(fila->tamanhoAtual == 0){
        return NULL;
    }
    void* temp = fila->elementos[0];
    fila->elementos[0] = fila->elementos[fila->tamanhoAtual-1];
    fila->tamanhoAtual--;
    descerElemento(fila, 0);
    return temp;
}
void descerElemento(Fila* fila, int i){
    while((2*i+1) < fila->tamanhoAtual){
        int base = i;
        int esq = 2*i+1;
        int dir = 2*i+2;
        if(fila->comparar(fila->elementos[esq], fila->elementos[base])){
            base = esq;
        }
        if (dir < fila->tamanhoAtual && fila->comparar(fila->elementos[dir], fila->elementos[base])){
            base = dir;
        }
        if (base == i){
            break;
        }
        void* temp = fila->elementos[base];
        fila->elementos[base] = fila->elementos[i];
        fila->elementos[i] = temp;
        i = base;
    }
}