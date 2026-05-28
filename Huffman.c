#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Huffman.h"
#include "heap.h"

#define ESPACO 5

int compararNos(void* A, void* B){
    No* noA = (No*) A;
    No* noB = (No*) B;
    return noA->frequencia < noB->frequencia;
}

//função para pré-processamento dos caracteres, necessário para construir a arvore huffman
int* lerCaracteres(char* nome){
    FILE* arquivo = fopen(nome, "r");
    if(arquivo == NULL){
        printf("Erro: não  foi possivel abrir o arquivo '%s'!!!\n", nome);
        return NULL;
    }
    int* tabelaFrequencia = calloc(256, sizeof(int));
    int c;
    while((c = fgetc(arquivo))!= EOF){
        tabelaFrequencia[c]++;
    }
    fclose(arquivo);
    return tabelaFrequencia;
}

void imprimirTabela(int *tabelaFrequencia){
    int contrabarra = 0;
    for(int i = 0; i < 256; i++){
        if(tabelaFrequencia[i] > 0){
            contrabarra++;
            printf("%c -> %d; " ,i , tabelaFrequencia[i]);
            if(contrabarra % 5 == 0){
                printf("\n");
            }

        }
    }
    printf("\n");
}

//função para colocar os elementos pré-processados na fila de prioridade
Fila* popularFila(int* tabelaFrequencia, int capacidadeMax){
    Fila* fila = criarFila(capacidadeMax);
    for(int i = 0; i < 256; i++){
        if(tabelaFrequencia[i] > 0){
            No* caractere = malloc(sizeof(No));
            caractere->codigo = (unsigned char) i;
            caractere->frequencia = tabelaFrequencia[i];
            caractere->esq = NULL;
            caractere->dir = NULL;
            inserirFila(fila, caractere, compararNos);
        }
    }
    return fila;
}


No* construirArvoreHuffman(Fila* fila){
    while(fila->tamanhoAtual >1){
        No* caractere1 = removerFila(fila, compararNos);
        No* caractere2 = removerFila(fila, compararNos);
        No* pai = malloc(sizeof(No));
        pai->codigo = '+';
        pai->frequencia = caractere1->frequencia + caractere2->frequencia;
        pai->esq = caractere1;
        pai->dir = caractere2;
        inserirFila(fila, pai, compararNos);
    }
    No* ultimo = (No*) removerFila(fila, compararNos);
    return ultimo;
}

void imprimirArvore(No* raiz, int nivel, char caminho[], int direita){
    if(raiz == NULL){
        return;
    }

    nivel++;

    imprimirArvore(raiz->dir, nivel, caminho, 1);

    if(nivel >= 2){
        caminho[nivel - 2] = 0;

        if(direita){
            caminho[nivel - 2] = 1;
        }
    }

    if(raiz->esq && nivel >= 1){
        caminho[nivel - 1] = 1;
    }

    printf("\n");

    for(int i = 0; i < nivel - 1; i++){

        if(i == nivel - 2)
            printf("+");

        else if(caminho[i])
            printf("|");

        else
            printf(" ");

        for(int j = 1; j < ESPACO; j++){

            if(i < nivel - 2)
                printf(" ");

            else
                printf("-");
        }
    }

    printf("%c:[%d]\n", raiz->codigo, raiz->frequencia);

    for(int i = 0; i < nivel; i++){

        if(caminho[i])
            printf("|");
        else
            printf(" ");

        for(int j = 1; j < ESPACO; j++){
            printf(" ");
        }
    }

    imprimirArvore(raiz->esq, nivel, caminho, 0);
}

void imprimirArvoreHorizontal(No* raiz){
    char caminho[255] = {0};

    imprimirArvore(raiz, 0, caminho, 0);

    printf("\n");
}

//função que vai gerar os codigos para cada caracter
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
    FILE* entrada = fopen(arquivoEntrada, "rb");
    if(entrada == NULL){
        printf("Erro ao abrir o arquivo de entrada!!!\n");
        return;
    }

    FILE* saida = fopen(arquivoSaida, "wb");
    if(saida == NULL){
        printf("Erro ao abrir o arquivo de saida!!!\n");
        return;
    }

    int frequencias[256] = {0};
    int c;

    while((c = fgetc(entrada)) != EOF){
        frequencias[c]++;
    }
    rewind(entrada);
    fwrite(frequencias, sizeof(int), 256, saida);

    unsigned char byte = 0;

    int contador = 0;
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

void descompactarArquivo(char* arquivoEntrada, char* arquivoSaida){
    FILE* entrada = fopen(arquivoEntrada, "rb");
    if(entrada == NULL){
        printf("Erro ao abrir o arquivo de entrada!!!\n");
        return;
    }

    FILE* saida = fopen(arquivoSaida, "wb"); 
    if(saida == NULL){
        printf("Erro ao abrir o arquivo de saida!!!\n");
        return;
    }

    int frequencias [256];
    fread(frequencias, sizeof(int),256, entrada);

    Fila *fila = criarFila(256);
    for(int i = 0; i < 256; i++){
        if(frequencias[i] > 0){
            No *novo = malloc(sizeof(No));
            novo->frequencia = frequencias[i];
            novo->codigo = i;
            novo->dir = NULL;
            novo->esq = NULL;
            inserirFila(fila, novo, compararNos);
        }
    }
    No *raiz = construirArvoreHuffman(fila);
    int totalCaracteres = 0;
    for(int i = 0; i < 256; i++){
        totalCaracteres += frequencias[i];
    }

    No *atual = raiz;

    unsigned char byte;

    int decodificados = 0;
    while(fread(&byte, sizeof(unsigned char), 1 , entrada) == 1 && decodificados < totalCaracteres){
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
                decodificados++;
                atual = raiz;

                if(decodificados == totalCaracteres) break;
            }
        }
    }
    fclose(entrada);
    fclose(saida);
}