#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "livro.h"
#include "arquivo.h"
#include "cabecalho.h"

void menu() {
    int option;
    int codigo = 0;
    cabecalho* cab = NULL;
    FILE *arqBin = NULL;
    FILE *arqTxt = NULL;
    
    // Nome padrão do arquivo binário e variáveis para manipulação de arquivos de texto
    char nome_arquivo_binario[] = "arquivo_binario.bin";
    char nome_arquivo_texto[50];
    char nome_auxiliar[200];
    char nome_autor[200];
    char nome_titulo[150];

    do {
        // Exibe o menu de opções para o usuário
        printf("\n--- Menu ---\n");
        printf("1. Cadastrar livro\n");
        printf("2. Remover livro\n");
        printf("3. Imprimir dados do livro\n");
        printf("4. Listar todos os livros\n");
        printf("5. Imprimir arvore por niveis\n");
        printf("6. Imprimir arvore por lista\n");
        printf("7. Buscar por autor\n");
        printf("8. Buscar por titulo\n");
        printf("9. Calcular total de livros cadastrados\n");
        printf("10. Imprimir lista de registros livres\n");
        printf("11. Carregar arquivo texto\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d%*c", &option);

        switch (option) {
            case 1:
                // Cadastra um novo livro no arquivo binário
                printf("Opcao 1: Cadastrar livro\n");
                
                livro* novo = cadastrar_livro();

                arqBin = fopen(nome_arquivo_binario, "r+b");

                // Se o arquivo binário não existir, cria um novo com o cabeçalho inicial
                if (arqBin == NULL) {
                    arqBin = fopen("arquivo_binario.bin", "w+b");
                    criar_lista_vazia(arqBin);
                }

                inserir_livro(arqBin, novo);

                cab = le_cabecalho(arqBin);
                cab->quantidade_livros++;
                escreve_cabecalho(arqBin, cab);
                free(cab);
                
                fclose(arqBin);
                free(novo);
                break;

            case 2:
                // Remove um livro com base no código fornecido pelo usuário
                printf("Opcao 2: Remover livro\n");
                
                arqBin = fopen(nome_arquivo_binario, "r+b");

                if (arqBin == NULL) {
                    printf("Arquivo binario nao encontrado!\n");
                    break;
                }

                printf("Digite o codigo: ");
                scanf("%d%*c", &codigo);

                // Função de remoção do livro com base no código
                remover_livro(arqBin, codigo);

                cab = le_cabecalho(arqBin);
                cab->quantidade_livros--;
                escreve_cabecalho(arqBin, cab);
                free(cab);

                fclose(arqBin);
                break;

            case 3:
            // Imprime os dados de um livro específico com base no código
                printf("Opcao 3: Imprimir dados do livro\n");

                arqBin = fopen(nome_arquivo_binario, "rb");

                if (arqBin == NULL) {
                    printf("Arquivo binario nao encontrado!\n");
                    break;
                }

                printf("Digite o codigo do livro: ");
                scanf("%d%*c", &codigo);

                // Função para imprimir o livro com base no código
                imprime_arquivo_codigo(arqBin, codigo);

                fclose(arqBin);
                break;

            case 4:
                // Lista todos os livros armazenados no arquivo binário
                printf("Opcao 4: Listar todos os livros\n");
                
                arqBin = fopen(nome_arquivo_binario, "rb");
                
                if (arqBin == NULL) {
                    printf("Arquivo binario nao encontrado!\n");
                    break;
                }

                // Função para imprimir todos os livros
                imprimir_arquivo_todos(arqBin);
                
                fclose(arqBin);
                break;

            case 5:
                printf("5. Imprimir arvore por niveis\n");

                arqBin = fopen(nome_arquivo_binario, "rb");
                
                if (arqBin == NULL) {
                    printf("Arquivo binario nao encontrado!\n");
                    break;
                }

                imprimir_arquivo_nivel(arqBin);

                fclose(arqBin);

                break;

            case 6:
                printf("6. Imprimir arvore por lista\n");

                arqBin = fopen(nome_arquivo_binario, "rb");

                if (arqBin == NULL) {
                    printf("Arquivo binario nao encontrado!\n");
                    break;
                }

                imprimir_arvore_lista(arqBin);

                fclose(arqBin);

                break;

            case 7:
                // Busca livros por autor e imprime os títulos encontrados
                printf("Opcao 7: Buscar por autor\n");

                arqBin = fopen(nome_arquivo_binario, "rb");

                if (arqBin == NULL) {
                    printf("Arquivo binario nao encontrado!\n");
                    break;
                }

                printf("Digite o nome do autor: ");
                scanf("%[^\n]%*c", nome_autor);

                printf("Titulo(s) do autor:\n");

                // Função para buscar por autor
                imprimir_arquivo_autor(arqBin, nome_autor);

                fclose(arqBin);
                break;

            case 8:
                // Busca livros por título e imprime os dados correspondentes
                printf("Opcao 8: Buscar por titulo\n");
                
                arqBin = fopen(nome_arquivo_binario, "rb");

                if (arqBin == NULL) {
                    printf("Arquivo binario nao encontrado!\n");
                    break;
                }
                
                printf("Digite o nome do titulo: ");
                scanf("%[^\n]%*c", nome_titulo);

                // Função para buscar por título
                imprimir_arquivo_titulo(arqBin, nome_titulo);

                fclose(arqBin);

                break;

            case 9:
                // Calcula e exibe o total de livros cadastrados no arquivo
                printf("Opcao 9: Calcular total de livros cadastrados\n");
                
                arqBin = fopen(nome_arquivo_binario, "rb");

                if (arqBin == NULL) {
                    printf("Arquivo binario nao encontrado!\n");
                    break;
                }

                // Função para contar e exibir a quantidade de livros
                printf("Quantidade de livros registrados: %d\n\n", contar_arquivo_quantidade(arqBin));

                fclose(arqBin);
                break;

            case 10:
                // Imprime a lista de registros livres no arquivo binário
                printf("Opcao 10: Imprimir lista de registros livres\n");
                
                arqBin = fopen(nome_arquivo_binario, "rb");

                if (arqBin == NULL) {
                    printf("Arquivo nao encontrado!\n");
                    break;
                }

                // Função para exibir a lista de registros livres
                mostrar_registro_livre(arqBin);

                fclose(arqBin);

                break;

            case 11:
                // Carrega dados de um arquivo texto para o arquivo binário
                printf("Opcao 11: Carregar arquivo texto\n");

                printf("Digite o nome do arquivo: ");
                scanf("%[^\n]%*c", nome_arquivo_texto);

                arqBin = fopen(nome_arquivo_binario, "r+b");
                arqTxt = fopen(nome_arquivo_texto, "r");

                if (arqTxt == NULL) {
                    printf("Arquivo com nome digitado nao encontrado!\n");
                    break;
                }

                if (arqBin == NULL) {
                    arqBin = fopen("arquivo_binario.bin", "w+b");
                    criar_lista_vazia(arqBin);
                }
                
                // Função para carregar o arquivo texto para o binário
                carregar_arquivo_para_binario(arqTxt, arqBin);

                fclose(arqTxt);
                fclose(arqBin);

                break;

            case 0:
                // Encerra o programa
                printf("Saindo...\n");
                break;

            default:
                // Informa ao usuário que a opção digitada é inválida
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (option != 0); // Repete o menu até o usuário escolher sair (opção 0)

    return;
}
