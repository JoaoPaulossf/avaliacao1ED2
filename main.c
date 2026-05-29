//GRUPO 11 - Carlos Eduardo de Oliveira Moronari / João Paulo Santos de Freitas / Marcus Vinicius Sabec Santana
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Huffman.h"

int main() {
    int opcao = 0;
    int menu = 1;
    char nomeArquivoEntrada[100];
    char nomeArquivoSaida[100];
    int* tabela_frequencia = NULL;
    Fila* fila = NULL;
    No* raiz_huffman = NULL;
    char dicionario[256][256] = {0};

    printf("\nBem vindo ao Compactador CEUNES\n");
    while (menu == 1) {
        printf("______MENU______\n");    
        printf("1. Comprimir Arquivo\n");
        printf("2. Exibir contagem de ocorrencias(Frequencia)\n");
        printf("3. Imprimir Arvore do codigo de huffman\n");
        printf("4. Descompactar Arquivo\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        if(scanf("%d", &opcao) != 1){
            opcao = 7;
            while (getchar() != '\n');
            continue;
        }
        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo .txt: ");
                scanf("%s", nomeArquivoEntrada);
                strcat(nomeArquivoEntrada,".txt");

                printf("Digite o nome do arquivo de saida: ");
                scanf("%s", nomeArquivoSaida);
                strcat(nomeArquivoSaida,".comp");

                tabela_frequencia = lerCaracteres(nomeArquivoEntrada);

                if(tabela_frequencia == NULL){
                    printf("Erro: não  foi possivel gerar a tabela de frequencias!!!\n");
                    break;
                }

                fila = popularFila(tabela_frequencia, 256);

                raiz_huffman = construirArvoreHuffman(fila);

                char caminho[256];

                gerarDicionario(dicionario, raiz_huffman, caminho, 0);

                printf("Compactando...\n");

                compactarArquivo(nomeArquivoEntrada, nomeArquivoSaida, dicionario);

                printf("Arquivo %s gerado!\n",nomeArquivoSaida);

                break;
            case 2:
                if (tabela_frequencia != NULL) {
                    imprimirTabela(tabela_frequencia);
                }else{ 
                    printf("ALERT: Você ainda não selecionou um arquivo para compressão.\n Qual arquivo deseja construir uma tabela de frequencia: ");
                    scanf("%s", nomeArquivoEntrada);
                    tabela_frequencia = lerCaracteres(nomeArquivoEntrada);

                    if(tabela_frequencia == NULL){
                        printf("Erro: não  foi possivel gerar a tabela de frequencias!!!\n");
                        break;
                    }
                    imprimirTabela(tabela_frequencia);
                }
                break;
            case 3:
                if (raiz_huffman == NULL) {
                    printf("ALERT: Você ainda não selecionou um arquivo.\n Qual arquivo deseja construir a Arvore de Huffman: ");
                    scanf("%s", nomeArquivoEntrada);
                    tabela_frequencia = lerCaracteres(nomeArquivoEntrada);

                    if(tabela_frequencia == NULL){
                        printf("Erro: não  foi possivel gerar a tabela de frequencias!!!\n");
                        break;
                    }
                    fila = popularFila(tabela_frequencia, 256);
                    raiz_huffman = construirArvoreHuffman(fila);
                    printf("\nEstrutura da Arvore:\n");
                    imprimirArvoreHorizontal(raiz_huffman);
                    printf("\n");
                    break;
                }
                printf("\nEstrutura da Arvore:\n");
                imprimirArvoreHorizontal(raiz_huffman);
                printf("\n");
                break;
            case 4:
                printf("Digite o nome do arquivo a ser descompactado:");
                scanf("%s", nomeArquivoEntrada);
                strcat(nomeArquivoEntrada,".comp");

                printf("Digite o nome do arquivo de saida:");
                scanf("%s", nomeArquivoSaida);
                strcat(nomeArquivoSaida,".txt");
                
                printf("Descompactando...\n");
                descompactarArquivo(nomeArquivoEntrada, nomeArquivoSaida, &tabela_frequencia, &raiz_huffman);
                printf("Arquivo %s gerado com sucesso!\n", nomeArquivoSaida);
                break;
        
            case 5:
                printf("Encerrando o programa...\n");
                menu = 2;
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }
    liberarArvore(raiz_huffman);
    liberarFila(fila);
    free(tabela_frequencia);
}