#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Huffman.h"
#include "heap.h"

int compararNos(void* A, void* B){
    No* noA = (No*) A;
    No* noB = (No*) B;
    if(noA->frequencia < noB->frequencia){
        return 1;
    }
    return 0;
}
int* lerCaracteres(char* nome){
    FILE* arquivo = fopen(nome, "r");
    if(arquivo == NULL)
        return NULL;
    int* tabelaFrequencia = calloc(256, sizeof(int));
    int c;
    while((c = fgetc(arquivo))!= EOF){
        tabelaFrequencia[c]++;
    }
    fclose(arquivo);
    return tabelaFrequencia;
}
Fila* popularFila(int* tabelaFrequencia, int capacidadeMax, int (*comparaElementos)(void*, void*)){
    Fila* fila = criarFila(capacidadeMax, comparaElementos);
    for(int i = 0; i < 256; i++){
        if(tabelaFrequencia[i] > 0){
            No* caractere = malloc(sizeof(No));
            caractere->codigo = (unsigned char) i;
            caractere->frequencia = tabelaFrequencia[i];
            caractere->esq = NULL;
            caractere->dir = NULL;
            inserirFila(fila, caractere);
        }
    }
    return fila;
}
No* construirArvoreHuffman(Fila* fila){
    while(fila->tamanhoAtual >1){
        No* caractere1 = (No*) removerFila(fila);
        No* caractere2 = (No*) removerFila(fila);
        No* pai = malloc(sizeof(No));
        pai->codigo = '+';
        pai->frequencia = caractere1->frequencia + caractere2->frequencia;
        pai->esq = caractere1;
        pai->dir = caractere2;
        inserirFila(fila, pai);
    }
    No* ultimo = (No*) removerFila(fila);
    return ultimo;
}
void imprimirArvore(No* raiz){
    if(raiz == NULL){
        return;
    }
    if(raiz->esq == NULL && raiz->dir == NULL){
        printf("[%c : %d]", raiz->codigo, raiz->frequencia);
    }
    else{
        printf("[%d]", raiz->frequencia);
    }
    imprimirArvore(raiz->esq);
    imprimirArvore(raiz->dir);
}
void gerarDicionario(char dicionario[256][256], No* raiz, char* caminho, int nivel){
    if(raiz == NULL){
        return;
    }
    if(raiz->esq == NULL && raiz->dir == NULL){
        caminho[nivel] = '\0';
        strcpy(dicionario[raiz->codigo], caminho);
    }
    else{
        caminho[nivel] = '0';
        gerarDicionario(dicionario, raiz->esq, caminho, nivel + 1);
        caminho[nivel] = '1';
        gerarDicionario(dicionario, raiz->dir, caminho, nivel + 1);
    }
}
void compactarArquivo(char* arquivoEntrada, char* arquivoSaida, char dicionario[256][256]){
    FILE* entrada = fopen(arquivoEntrada, "r");
    FILE* saida = fopen(arquivoSaida, "wb");
    if(entrada == NULL || saida == NULL){
        printf("Erro ao abrir os arquivos!\n");
        return;
    }
    unsigned char byte = 0;
    int contador = 0;
    int c;
    while((c = fgetc(entrada)) != EOF){
        char* codigo = dicionario[c];
        for(int i = 0; codigo[i] != '\0'; i++){
            byte = byte << 1;
            if(codigo[i] == '1'){
                byte = byte | 1;
            }
            contador++;
            if(contador == 8){
                fwrite(&byte, sizeof(unsigned char), 1, saida);
                byte = 0;
                contador = 0;
            }
        }
    }
    if(contador > 0){
        byte = byte << (8 - contador);
        fwrite(&byte, sizeof(unsigned char), 1, saida);
    }
    fclose(entrada);
    fclose(saida);
}
void descompactarArquivo(No* raiz, char* arquivoEntrada, char* arquivoSaida){
    FILE* entrada = fopen(arquivoEntrada, "rb");
    FILE* saida = fopen(arquivoSaida, "w"); 
    if(entrada == NULL || saida == NULL){
        printf("ERROR");
        return;
    }
    No* atual = raiz;
    unsigned char byte;
    while(fread(&byte, sizeof(unsigned char), 1 , entrada) == 1){
        for(int i = 7 ; i >= 0; i--){
            int bit = (byte >> i) & 1;
            if(bit == 0){
                atual = atual->esq;
            }
            else{
                atual = atual->dir;
            }
            if(atual->esq == NULL && atual->dir == NULL){
                fputc(atual->codigo, saida);
                atual = raiz;
            }
        }
    }
    fclose(entrada);
    fclose(saida);
}