#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "livro.h"
#include "arquivo.h"

// Função para cadastrar um novo livro solicitando dados do usuário
// Entrada: Nenhuma
// Saída: Retorna um ponteiro para o registro de livro preenchido
// Pré-Condição: Nenhuma
// Pós-Condição: Um novo livro é criado com os dados fornecidos pelo usuário
livro* cadastrar_livro() {
    livro* novo_livro = (livro*) malloc (sizeof (livro) );
    
    printf ("\nDigite o codigo: ");
    scanf ("%d%*c", &novo_livro->codigo);

    printf ("Digite o titulo: ");
    scanf ("%[^\n]%*c", novo_livro->titulo);

    printf ("Digite o autor: ");
    scanf ("%[^\n]%*c", novo_livro->autor);

    printf ("Digite a editora: ");
    scanf ("%[^\n]%*c", novo_livro->editora);

    printf ("Digite a edicao: ");
    scanf ("%d%*c", &novo_livro->edicao);

    printf ("Digite o ano: ");
    scanf ("%d%*c", &novo_livro->ano);

    printf ("Digite o preco: ");
    scanf ("%f%*c", &novo_livro->preco);

    printf ("Digite o estoque: ");
    scanf ("%d%*c", &novo_livro->estoque);

    return novo_livro;
}

// Função para imprimir as informações de um livro
// Entrada: Ponteiro para o registro de livro
// Saída: Nenhuma (imprime os dados do livro)
// Pré-Condição: O ponteiro info deve apontar para um livro válido
// Pós-Condição: As informações do livro são exibidas na tela
void imprimir_livro(livro *info) {
    printf("\nInformacoes do Livro:\n");
    printf("Codigo: %d\n", info->codigo);
    printf("Titulo: %s\n", info->titulo);
    printf("Autor: %s\n", info->autor);
    printf("Editora: %s\n", info->editora);
    printf("Edicao: %d\n", info->edicao);
    printf("Ano: %d\n", info->ano);
    printf("Preco: R$%.2f\n", info->preco);
    printf("Estoque: %d\n", info->estoque);
    printf("Proxima esquerda: %d\n" , info->esquerda);
    printf ("Proxima direita: %d\n", info->direita);

}

// Função para copiar as informações de um livro para um novo registro
// Entrada: Ponteiro para o livro original
// Saída: Estrutura de livro com as informações copiadas
// Pré-Condição: O ponteiro info deve apontar para um livro válido
// Pós-Condição: As informações do livro são copiadas para uma nova estrutura
livro copiar_info_livro(livro* info) {
    livro info_livro;

    info_livro.codigo = info->codigo;
    
    strcpy(info_livro.titulo, info->titulo);
    strcpy(info_livro.autor, info->autor);
    strcpy(info_livro.editora, info->editora);
    info_livro.edicao = info->edicao;
    info_livro.ano = info->ano;
    info_livro.preco = info->preco;
    info_livro.estoque = info->estoque;

    return info_livro;
}

// Função para copiar informações de um livro a partir de strings auxiliares
// Entrada: Ponteiro para o livro e estrutura de strings auxiliares com informações do livro
// Saída: Nenhuma
// Pré-Condição: As strings auxiliares devem conter dados válidos e formatados
// Pós-Condição: As informações da estrutura auxiliar são copiadas para o registro de livro
void copiar_info_livro_str(livro* info, livro_auxiliar_str nova_info) {
    info->codigo = atoi(nova_info.codigo); //printf("o codigo eh %d\n", info->codigo);

    strcpy(info->titulo, nova_info.titulo); //printf("titulo eh %s\n", info->titulo);
    strcpy(info->autor, nova_info.autor);   //printf("autor eh %s\n", info->autor);
    strcpy(info->editora, nova_info.editora);   //printf("editora eh %s\n", info->editora);

    info->edicao = atoi(nova_info.edicao); //printf("edicaoo eh %d\n", info->titulo);
    info->ano = atoi(nova_info.ano);        //printf("ano eh %d\n", info->ano);
    info->preco = converter_string_float(nova_info.preco); //printf("preco eh %f\n", info->preco);
    info->estoque = atoi(nova_info.estoque);    //printf("estoque eh %d\n", info->estoque);    

    info->esquerda = -1;
    info->direita = -1;
}