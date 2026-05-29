//GRUPO 11 - Carlos Eduardo de Oliveira Moronari / João Paulo Santos de Freitas / Marcus Vinicius Sabec Santana
#ifndef HEAP_H
#define HEAP_H

typedef struct fila{
    void **elementos;
    int tamanhoTotal;
    int tamanhoAtual;
}Fila;

Fila *criarFila(int n);

void inserirFila(Fila *fila, void *novoElemento, int(*comparar)(void*, void*));

void subirElemento(Fila *fila, int i, int(*comparar)(void*, void*));

void* removerFila(Fila* fila, int(*comparar)(void*, void*));

void descerElemento(Fila* fila,int i, int(*comparar)(void*, void*));

#endif