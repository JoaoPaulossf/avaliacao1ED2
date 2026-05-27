#ifndef HEAP_H
#define HEAP_H

struct NoHuffman;
typedef struct NoHuffman No;

typedef struct fila{
    void **elementos;
    int tamanhoTotal;
    int tamanhoAtual;
}Fila;

Fila *criarFila(int n);

void inserirFila(Fila *fila, void *novoElemento, int(*comparar)(void*, void*));

void subirElemento(Fila *fila, int i, int(*comparar)(void*, void*));

No* removerFila(Fila* fila, int(*comparar)(void*, void*));

void descerElemento(Fila* fila,int i, int(*comparar)(void*, void*));

#endif