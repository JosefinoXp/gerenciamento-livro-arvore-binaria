#ifndef livro_H_INCLUDED
#define livro_H_INCLUDED
#define MAX 200

typedef struct {
    int codigo;
    char titulo[150];
    char autor[200];
    char editora[50];
    int edicao;
    int ano;
    float preco;
    int estoque;
    int direita;
    int esquerda;
} livro;

typedef struct {
    char codigo[MAX];
    char titulo[MAX];
    char autor[MAX];
    char editora[MAX];
    char edicao[MAX];
    char ano[MAX];
    char preco[MAX];
    char estoque[MAX];
} livro_auxiliar_str;

// Função para cadastrar um novo livro solicitando dados do usuário
// Entrada: Nenhuma
// Saída: Retorna um ponteiro para o registro de livro preenchido
// Pré-Condição: Nenhuma
// Pós-Condição: Um novo livro é criado com os dados fornecidos pelo usuário
livro* cadastrar_livro();

// Função para imprimir as informações de um livro
// Entrada: Ponteiro para o registro de livro
// Saída: Nenhuma (imprime os dados do livro)
// Pré-Condição: O ponteiro info deve apontar para um livro válido
// Pós-Condição: As informações do livro são exibidas na tela
void imprimir_livro(livro *info);

// Função para copiar as informações de um livro para um novo registro
// Entrada: Ponteiro para o livro original
// Saída: Estrutura de livro com as informações copiadas
// Pré-Condição: O ponteiro info deve apontar para um livro válido
// Pós-Condição: As informações do livro são copiadas para uma nova estrutura
livro copiar_info_livro(livro* info);

// Função para copiar informações de um livro a partir de strings auxiliares
// Entrada: Ponteiro para o livro e estrutura de strings auxiliares com informações do livro
// Saída: Nenhuma
// Pré-Condição: As strings auxiliares devem conter dados válidos e formatados
// Pós-Condição: As informações da estrutura auxiliar são copiadas para o registro de livro
void copiar_info_livro_str(livro* info, livro_auxiliar_str nova_info);

#endif