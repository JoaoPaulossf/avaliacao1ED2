#ifndef HEAP_H
#define HEAP_H

struct NoHuffman;
typedef struct NoHuffman No;

typedef struct fila{
    No** elementos;
    int tamanhoTotal;
    int tamanhoAtual;
}Fila;

Fila *criarFila(int n);

void inserirFila(Fila* fila, No* novoElemento);

void subirElemento(Fila* fila, int i);

No* removerFila(Fila* fila);

void descerElemento(Fila* fila,int i);

#endif