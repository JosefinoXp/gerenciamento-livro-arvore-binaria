#ifndef cabecalho_H_INCLUDED
#define cabecalho_H_INCLUDED
#include "livro.h"

typedef struct {
    int pos_cabeca;
    int pos_topo;
    int pos_livre;
    int quantidade_livros;
} cabecalho;

//Criar lista nova em arquivo
//Pré-Condição: arquivo aberto para leitura/escrita
//Pós-condição: arquivo é inicializado com uma lista vazia
void criar_lista_vazia (FILE* arq);

//Escreve livro arquivo o cabecalho contendo as informacoes da lista
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//Pos-condicao: cabecalho escrito livro arquivo
void escreve_cabecalho(FILE* arq, cabecalho* cab);

//Le o cabecalho do arquivo contendo as informacoes da lista
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//Pos-condicao: retorna o ponteiro para o cabecalho lido
cabecalho* le_cabecalho(FILE * arq);

//le um livro em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//pos deve ser uma posicao valida da lista
//Pos-condicao: ponteiro para livro lido e retornado
livro* le_livro(FILE* arq, int pos);

//Escreve um livro em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// pos deve ser uma posicao valida do arquivo
//Pos-condicao: livro escrito no arquivo
void escreve_livro(FILE* arq, livro* novo_livro, int pos);

#endif