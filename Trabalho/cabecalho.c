#include <stdio.h>
#include <stdlib.h>

#include "cabecalho.h"
#include "livro.h"

// Descrição: Cria uma lista vazia e inicializa seu cabeçalho.
// Pre-condicao: O ponteiro 'arq' deve ser um ponteiro válido para um arquivo aberto em modo de escrita
// Pos-condicao: O cabeçalho da lista é gravado no arquivo
void criar_lista_vazia (FILE* arq) {
    cabecalho * cab = (cabecalho*) malloc (sizeof(cabecalho));
    cab->pos_cabeca = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;
    cab->quantidade_livros = 0;
    escreve_cabecalho(arq, cab);
    free(cab);
}

//Escreve no arquivo o cabecalho contendo as informacoes da lista
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//Pos-condicao: cabecalho escrito no arquivo
void escreve_cabecalho(FILE* arq, cabecalho* cab) {
    fseek(arq, 0, SEEK_SET); //posiciona no inıcio do arquivo
    fwrite(cab, sizeof(cabecalho), 1, arq);
}

//Le o cabecalho do arquivo contendo as informacoes da lista
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//Pos-condicao: retorna o ponteiro para o cabecalho lido
cabecalho* le_cabecalho(FILE * arq) {
    cabecalho * cab = (cabecalho*) malloc(sizeof(cabecalho));
    fseek(arq,0,SEEK_SET); // posiciona no inıcio do arquivo
    fread(cab,sizeof(cabecalho),1,arq);
    return cab;
}

//le um livro em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//pos deve ser uma posicao valida da lista
//Pos-condicao: ponteiro para livro lido e retornado
livro* le_livro(FILE* arq, int pos) {
    livro* livro_lido = malloc( sizeof(livro) );
    fseek(arq, sizeof(cabecalho) + pos*sizeof(livro), SEEK_SET);
    fread(livro_lido, sizeof(livro), 1, arq);
    return livro_lido;
}

//Escreve um livro em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// pos deve ser uma posicao valida do arquivo
//Pos-condicao: livro escrito no arquivo
void escreve_livro(FILE* arq, livro* novo_livro, int pos) {
    fseek(arq, sizeof(cabecalho) + pos*sizeof(livro), SEEK_SET);
    fwrite(novo_livro, sizeof(livro), 1, arq);
}
