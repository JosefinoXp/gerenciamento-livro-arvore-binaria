#ifndef arquivo_H_INCLUDED
#define arquivo_H_INCLUDED
#include "livro.h"
#include "cabecalho.h"

//Descrição: Insere um novo livro na árvore binária de livros.
//Pré-condição: O arquivo deve estar aberto e acessível.
//Pós-condição: O novo livro é inserido na posição correta na árvore. O cabeçalho do arquivo é atualizado.
void inserir_livro(FILE *arq, livro *novo_livro);

//Descrição: Remove um livro da árvore binária com base no código fornecido.
//Pré-condição: O arquivo deve estar aberto e acessível.
//Pós-condição: O livro com o código especificado é removido da árvore, se encontrado. O cabeçalho do arquivo é atualizado.
void remover_livro(FILE *arq, int codigo);

//Descrição: Função auxiliar que realiza a remoção de um nó na árvore binária de forma recursiva.
//Pré-condição: O arquivo deve estar aberto e acessível.
//Pós-condição: O nó correspondente ao código especificado é removido da árvore, se encontrado.
int remover_no(FILE *arq, int pos_atual, int codigo, cabecalho *cab);

//Descrição: Encontra o sucessor (menor valor) na subárvore direita de um nó.
//Pré-condição: O arquivo deve estar aberto e acessível. pos_atual deve ser uma posição válida na árvore.
//Pós-condição: Retorna a posição do sucessor na subárvore direita.
int encontrar_sucessor(FILE *arq, int pos_atual);

//Descrição: Atualiza o "registro livre" no cabeçalho após a remoção de um livro.
//Pré-condição: O arquivo deve estar aberto e acessível. pos_removida deve ser uma posição válida.
//Pós-condição: O livro removido é atualizado para apontar para o registro livre, e o cabeçalho é atualizado.
void atualizar_registro_livre(FILE *arq, int pos_removida, cabecalho *cab);


// Descrição: Imprime as informações de todos os livros presentes no arquivo binário.
// Pré-Condicao: O arquivo binário deve estar aberto em modo de leitura.
// Pós-Condicao: As informações de todos os livros são impressas no console.
void imprimir_arquivo_todos(FILE* arq);

//Descrição: Imprime os livros em níveis, mostrando todos os nós em cada nível da árvore.
//Pré-condição: O arquivo deve estar aberto e acessível.
//Pós-condição: Os livros são impressos em níveis no console.
void imprimir_arquivo_nivel(FILE* arq);

//Descrição: Função auxiliar que imprime a árvore binária de forma recursiva.
//Pré-condição: O arquivo deve estar aberto e acessível. pos deve ser uma posição válida na árvore.
//Pós-condição: A árvore é impressa no formato de lista.
void imprimir_arvore_aux(FILE *arq, int pos);

//Descrição: Imprime a árvore binária em formato de lista.
//Pré-condição: O arquivo deve estar aberto e acessível.
//Pós-condição: A árvore é impressa no console.
void imprimir_arvore_lista(FILE *arq);

//Descrição: Imprime as informações de um livro específico com base no código fornecido.
//Pré-condição: O arquivo deve estar aberto em modo de leitura. O código deve ser um valor válido para busca na árvore.
//Pós-condição: As informações do livro correspondente ao código são exibidas no console, se encontrado. Se o livro não for encontrado, uma mensagem de erro é exibida.
void imprime_arquivo_codigo(FILE* arq, int codigo);

//Descrição: Imprime os livros de um autor específico.
//Pré-condição: O arquivo deve estar aberto em modo de leitura.
//Pós-condição: Os livros do autor especificado são exibidos no console. Se nenhum livro for encontrado, uma mensagem é exibida.
void imprimir_arquivo_autor(FILE* arq, char nome_autor[]);

//Descrição: Função auxiliar que percorre a árvore binária para encontrar e imprimir livros de um autor específico.
//Pré-condição: O arquivo deve estar aberto e acessível. pos_atual deve ser uma posição válida na árvore.
//Pós-condição: Os livros do autor especificado são impressos, se encontrados.
void percorrer_arquivo_autor(FILE* arq, int pos_atual, char nome_autor[], int* encontrado);

//Descrição: Imprime os livros com um título específico.
//Pré-condição: O arquivo deve estar aberto em modo de leitura.
//Pós-condição: Os livros com o título especificado são exibidos no console. Se nenhum livro for encontrado, uma mensagem é exibida.
void imprimir_arquivo_titulo(FILE* arq, char nome_titulo[]);

//Descrição: Função auxiliar que percorre a árvore binária para encontrar e imprimir livros com um título específico.
//Pré-condição: O arquivo deve estar aberto e acessível. pos_atual deve ser uma posição válida na árvore.
//Pós-condição: O livro com o título especificado é impresso, se encontrado.
void percorrer_arquivo_titulo(FILE* arq, int pos_atual, char nome_titulo[], int* encontrado);

//Descrição: Conta a quantidade total de livros no arquivo binário.
//Pré-condição: O arquivo deve estar aberto em modo de leitura.
//Pós-condição: Retorna a quantidade total de livros no arquivo.
int contar_arquivo_quantidade(FILE* arqBin);

//Descrição: Exibe todos os livros presentes na árvore binária.
//Pré-condição: O arquivo deve estar aberto e acessível. pos_atual deve ser uma posição válida na árvore.
//Pós-condição: Todos os livros na árvore são exibidos no console.
void exibir_livros(FILE *arq, int pos_atual);

//Descrição: Mostra as posições dos registros livres no arquivo binário.
//Pré-condição: O arquivo deve estar aberto em modo de leitura.
//Pós-condição: As posições dos registros livres são exibidas no console. Se não houver registros livres, uma mensagem informando que nenhum livro foi encontrado é exibida.
void mostrar_registro_livre(FILE* arqBin);

// Descrição: Remove espaços em branco no início e no final de cada campo de um struct 'livro_auxiliar_str'.
// Pré-Condicao: O struct 'livro_auxiliar_str' deve estar corretamente preenchido.
// Pós-Condicao: Campos do struct 'livro_auxiliar_str' são retornados sem espaços em branco.
livro_auxiliar_str filtrar_espaco(livro_auxiliar_str aux);

// Descrição: Converte uma string de preço para um float, substituindo vírgulas por pontos.
// Pré-Condicao: A string de entrada deve estar formatada corretamente como um número.
// Pós-Condicao: A string é convertida para float.
float converter_string_float(char preco_str[]);

// Descrição: Remove espaços em branco no início e no fim de uma string.
// Pré-Condicao: A string de entrada deve ser uma string válida e não nula.
// Pós-Condicao: A string é retornada com espaços em branco removidos.
char* ignorar_espaco(char *str);

// Descrição: Carrega os dados de um arquivo de texto e insere os registros no arquivo binário.
// Pré-Condicao: Ambos os arquivos devem estar abertos nos modos apropriados (texto para leitura, binário para escrita).
// Pós-Condicao: Dados do arquivo de texto são inseridos no arquivo binário.
void carregar_arquivo_para_binario(FILE* arqTxt, FILE* arqBin);


#endif