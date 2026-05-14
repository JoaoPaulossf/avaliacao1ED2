#ifndef HEAP_H
#define HEAP_H

typedef struct fila{
    void** elementos;
    int tamanhoTotal;
    int tamanhoAtual;
    int (*comparar)(void*, void*);
}Fila;
Fila *criarFila(int n, int (*comparaElementos)(void*, void*));
void inserirFila(Fila* fila, void* novoElemento);
void subirElemento(Fila* fila, int i);
void* removerFila(Fila* fila);
void descerElemento(Fila* fila,int i);

#endif