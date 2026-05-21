#include <stdio.h>
#include <stdlib.h>
#include "Huffman.h"

int main() {
    int opcao = 0;
    char nomeArquivoEntrada[100];
    char nomeArquivoSaida[100];
    int* tabela_frequencia = NULL;
    Fila* fila = NULL;
    No* raiz_huffman = NULL;
    char dicionario[256][256] = {0};

    while (opcao != 6) {
        printf("\nBem vindo ao Compactador CEUNES\n");
        printf("1. Ler arquivo texto\n");
        printf("2. Contar ocorrencias (Frequencia)\n");
        printf("3. Construir e Imprimir Arvore\n");
        printf("4. Compactar Arquivo\n");
        printf("5. Descompactar Arquivo\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo .txt: ");
                scanf("%s", nomeArquivoEntrada);
                printf("Arquivo selecionado para operacoes!\n");
                printf("Digite o nome do arquivo de saida: ");
                scanf("%s", nomeArquivoSaida);
                printf("Nome salvo para operacoes!\n");
                break;
            case 2:
                tabela_frequencia = lerCaracteres(nomeArquivoEntrada);
                if (tabela_frequencia != NULL) {
                    printf("Frequencias calculadas com sucesso!\n");
                }
                break;
            case 3:
                if (tabela_frequencia == NULL) {
                    printf("Erro: Calcule as frequencias primeiro (Opcao 2)!\n");
                    break;
                }
                fila = popularFila(tabela_frequencia, 256, compararNos);
                raiz_huffman = construirArvoreHuffman(fila);
                
                printf("\nEstrutura da Arvore:\n");
                imprimirArvore(raiz_huffman, 0);
                printf("\n");
                char caminho[256];
                gerarDicionario(dicionario, raiz_huffman, caminho, 0);
                break;
            case 4:
                if (raiz_huffman == NULL) {
                    printf("Erro: Construa a arvore primeiro (Opcao 3)!\n");
                    break;
                }
                printf("Compactando...\n");
                compactarArquivo(nomeArquivoEntrada, "saida.comp", dicionario);
                printf("Arquivo saida.comp gerado!\n");
                break;
            case 5:
                if (raiz_huffman == NULL) {
                    printf("Erro: A arvore precisa estar na memoria para descompactar!\n");
                    break;
                }
                printf("Descompactando...\n");
                descompactarArquivo(raiz_huffman, "saida.comp", "restaurado.txt");
                printf("Arquivo restaurado.txt gerado com sucesso!\n");
                break;
            case 6:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }
}