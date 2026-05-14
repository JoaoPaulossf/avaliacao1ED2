#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap.h"

typedef struct NoHuffman{
    unsigned char codigo;
    int frequencia;
    struct NoHuffman* esq;
    struct NoHuffman* dir;
}No;
int compararNos(void* A, void* B);
int* lerCaracteres(char* nome);
Fila* popularFila(int* tabelaFrequencia, int capacidadeMax, int (*comparaElementos)(void*, void*));
No* construirArvoreHuffman(Fila* fila);
void imprimirArvore(No* raiz);
void gerarDicionario(char dicionario[256][256], No* raiz, char* caminho, int nivel);
void compactarArquivo(char* arquivoEntrada, char* arquivoSaida, char dicionario[256][256]);
void descompactarArquivo(No* raiz, char* arquivoEntrada, char* arquivoSaida);
#endif