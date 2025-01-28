#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "arquivo.h"
#include "livro.h"
#include "cabecalho.h"

//Descrição: Insere um novo livro na árvore binária de livros.
//Pré-condição: O arquivo deve estar aberto e acessível.
//Pós-condição: O novo livro é inserido na posição correta na árvore. O cabeçalho do arquivo é atualizado.
void inserir_livro(FILE *arq, livro *novo_livro) {
    // Ler o cabeçalho do arquivo
    cabecalho *cab = le_cabecalho(arq);

    printf ("%d %d %d\n", cab->pos_cabeca, cab->pos_topo, cab->pos_livre);

    // Criar uma cópia do novo livro
    livro x = copiar_info_livro(novo_livro);
    x.direita = -1;
    x.esquerda = -1;

    // Se a árvore estiver vazia, insere o primeiro livro como raiz
    if (cab->pos_cabeca == -1) {
        escreve_livro(arq, &x, cab->pos_topo);  // Escreve o livro no topo
        cab->pos_cabeca = cab->pos_topo;  // Define o topo como a raiz
        cab->pos_topo++;  // Atualiza a posição do topo para a próxima inserção
        escreve_cabecalho(arq, cab);  // Atualiza o cabeçalho no arquivo
    } 
    else {
        // Percorrer a árvore para encontrar o local de inserção
        int pos_atual = cab->pos_cabeca;

        while (1) {
            // Ler o livro atual da árvore
            livro *livro_atual = le_livro(arq, pos_atual);

            // Inserir à esquerda se o código for menor
            if (novo_livro->codigo < livro_atual->codigo) {
                if (livro_atual->esquerda == -1) {
                    livro_atual->esquerda = cab->pos_topo;  // Atualizar o ponteiro para o novo nó
                    escreve_livro(arq, livro_atual, pos_atual);  // Atualizar o nó atual no arquivo
                    escreve_livro(arq, &x, cab->pos_topo);  // Escrever o novo livro no topo
                    cab->pos_topo++;  // Atualizar o topo
                    escreve_cabecalho(arq, cab);  // Atualizar o cabeçalho
                    break;
                } else {
                    pos_atual = livro_atual->esquerda;  // Continuar descendo à esquerda
                }
            }
            // Inserir à direita se o código for maior
            else if (novo_livro->codigo > livro_atual->codigo) {
                if (livro_atual->direita == -1) {
                    livro_atual->direita = cab->pos_topo;  // Atualizar o ponteiro para o novo nó
                    escreve_livro(arq, livro_atual, pos_atual);  // Atualizar o nó atual no arquivo
                    escreve_livro(arq, &x, cab->pos_topo);  // Escrever o novo livro no topo
                    cab->pos_topo++;  // Atualizar o topo
                    escreve_cabecalho(arq, cab);  // Atualizar o cabeçalho
                    break;
                } else {
                    pos_atual = livro_atual->direita;  // Continuar descendo à direita
                }
            } else {
                // Livro com código duplicado, não inserir
                printf("Erro: Código de livro duplicado.\n");
                break;
            }

            // Libere a memória de `livro_atual` somente quando não for mais necessário
            free(livro_atual);
        }
    }

    // Libere a memória do cabeçalho
    free(cab);
}

//Descrição: Remove um livro da árvore binária com base no código fornecido.
//Pré-condição: O arquivo deve estar aberto e acessível.
//Pós-condição: O livro com o código especificado é removido da árvore, se encontrado. O cabeçalho do arquivo é atualizado.
void remover_livro(FILE *arq, int codigo) {
    // Ler o cabeçalho do arquivo
    cabecalho *cab = le_cabecalho(arq);

    // Verificar se a árvore está vazia
    if (cab->pos_cabeca == -1) {
        printf("Erro: A árvore está vazia.\n");
        free(cab);
        return;
    }

    // Chama a função auxiliar para iniciar a remoção a partir da raiz
    cab->pos_cabeca = remover_no(arq, cab->pos_cabeca, codigo, cab);
    escreve_cabecalho(arq, cab);
    free(cab);
}

//Descrição: Função auxiliar que realiza a remoção de um nó na árvore binária de forma recursiva.
//Pré-condição: O arquivo deve estar aberto e acessível.
//Pós-condição: O nó correspondente ao código especificado é removido da árvore, se encontrado.
int remover_no(FILE *arq, int pos_atual, int codigo, cabecalho *cab) {
    if (pos_atual == -1) {
        printf("Erro: Livro não encontrado.\n");
        return -1;
    }

    livro *livro_atual = le_livro(arq, pos_atual);

    // Verifica se o código é menor (vai para a esquerda)
    if (codigo < livro_atual->codigo) {
        livro_atual->esquerda = remover_no(arq, livro_atual->esquerda, codigo, cab);
        escreve_livro(arq, livro_atual, pos_atual);
    } 
    // Verifica se o código é maior (vai para a direita)
    else if (codigo > livro_atual->codigo) {
        livro_atual->direita = remover_no(arq, livro_atual->direita, codigo, cab);
        escreve_livro(arq, livro_atual, pos_atual);
    }
    // Caso o código seja igual, encontramos o nó a ser removido
    else {
        // Caso 1: Nó sem filhos (folha)
        if (livro_atual->esquerda == -1 && livro_atual->direita == -1) {
            atualizar_registro_livre(arq, pos_atual, cab);  // Atualiza o "registro livre"
            free(livro_atual);
            return -1;
        }

        // Caso 2: Nó com apenas um filho
        if (livro_atual->esquerda == -1) {
            int direita = livro_atual->direita;
            atualizar_registro_livre(arq, pos_atual, cab);  // Atualiza o "registro livre"
            free(livro_atual);
            return direita;  // Retorna o filho à direita
        }
        if (livro_atual->direita == -1) {
            int esquerda = livro_atual->esquerda;
            atualizar_registro_livre(arq, pos_atual, cab);  // Atualiza o "registro livre"
            free(livro_atual);
            return esquerda;  // Retorna o filho à esquerda
        }

        // Caso 3: Nó com dois filhos
        // Encontra o sucessor (menor valor da subárvore à direita)
        int sucessor_pos = encontrar_sucessor(arq, livro_atual->direita);
        livro *sucessor = le_livro(arq, sucessor_pos);

        // Substitui os dados do nó atual pelo sucessor
        livro_atual->codigo = sucessor->codigo;
        strcpy(livro_atual->titulo, sucessor->titulo);
        strcpy(livro_atual->autor, sucessor->autor);
        strcpy(livro_atual->editora, sucessor->editora);
        livro_atual->edicao = sucessor->edicao;
        livro_atual->ano = sucessor->ano;
        livro_atual->preco = sucessor->preco;
        livro_atual->estoque = sucessor->estoque;

        // Remove o sucessor na subárvore à direita
        livro_atual->direita = remover_no(arq, livro_atual->direita, sucessor->codigo, cab);
        escreve_livro(arq, livro_atual, pos_atual);

        free(sucessor);
    }

    free(livro_atual);
    return pos_atual;
}

//Descrição: Encontra o sucessor (menor valor) na subárvore direita de um nó.
//Pré-condição: O arquivo deve estar aberto e acessível. pos_atual deve ser uma posição válida na árvore.
//Pós-condição: Retorna a posição do sucessor na subárvore direita.
int encontrar_sucessor(FILE *arq, int pos_atual) {
    while (1) {
        livro *livro_atual = le_livro(arq, pos_atual);
        if (livro_atual->esquerda == -1) {
            int pos_sucessor = pos_atual;
            free(livro_atual);
            return pos_sucessor;
        }
        pos_atual = livro_atual->esquerda;
        free(livro_atual);
    }
}

//Descrição: Atualiza o "registro livre" no cabeçalho após a remoção de um livro.
//Pré-condição: O arquivo deve estar aberto e acessível. pos_removida deve ser uma posição válida.
//Pós-condição: O livro removido é atualizado para apontar para o registro livre, e o cabeçalho é atualizado.
void atualizar_registro_livre(FILE *arq, int pos_removida, cabecalho *cab) {
    // Ler o livro que foi removido
    livro *livro_removido = le_livro(arq, pos_removida);

    // Apontar o livro removido para o atual "registro livre"
    livro_removido->esquerda = cab->pos_livre;

    // Atualizar o "registro livre" no cabeçalho
    cab->pos_livre = pos_removida;

    // Gravar o livro atualizado e o cabeçalho de volta no arquivo
    escreve_livro(arq, livro_removido, pos_removida);
    escreve_cabecalho(arq, cab);

    free(livro_removido);
}


// Descrição: Imprime as informações de todos os livros presentes no arquivo binário.
// Pré-Condicao: O arquivo binário deve estar aberto em modo de leitura.
// Pós-Condicao: As informações de todos os livros são impressas no console.
void imprimir_arquivo_todos(FILE* arq) {
    cabecalho* cab = le_cabecalho(arq);

    printf ("%d %d %d\n", cab->pos_cabeca, cab->pos_topo, cab->pos_livre);
    
    if (cab->pos_cabeca == -1) {
        printf ("\nNenhum livro encontrado!\n");
        free(cab);
        return;
    }

    exibir_livros(arq, cab->pos_cabeca);

    free(cab);
}
//Descrição: Função auxiliar que imprime a árvore binária de forma recursiva.
//Pré-condição: O arquivo deve estar aberto e acessível. pos deve ser uma posição válida na árvore.
//Pós-condição: A árvore é impressa no formato de lista.
void imprimir_arvore_aux(FILE *arq, int pos) {
    if (pos == -1) {
        printf("[]");
        return;
    }

    livro *l = le_livro(arq, pos);
    // imprimir_livro(l);
    printf("[%d, ", l->codigo);
    imprimir_arvore_aux(arq, l->esquerda);
    printf(", ");
    imprimir_arvore_aux(arq, l->direita);
    printf("]");

    free(l);
}
//Descrição: Imprime a árvore binária em formato de lista.
//Pré-condição: O arquivo deve estar aberto e acessível.
//Pós-condição: A árvore é impressa no console.
void imprimir_arvore_lista(FILE *arq) {
    cabecalho* cab = le_cabecalho(arq);

    if (cab->pos_cabeca == -1 || arq == NULL) {
        printf ("[]\n");
        free(cab);
    }

    printf ("\n%d %d %d\n", cab->pos_cabeca, cab->pos_topo, cab->pos_livre);

    imprimir_arvore_aux(arq, cab->pos_cabeca);

    free(cab);
}
//Descrição: Imprime os livros em níveis, mostrando todos os nós em cada nível da árvore.
//Pré-condição: O arquivo deve estar aberto e acessível.
//Pós-condição: Os livros são impressos em níveis no console.
void imprimir_arquivo_nivel(FILE* arq) {
    cabecalho* cab = NULL;
    livro *no = NULL;
    fseek(arq, 0, SEEK_SET);

    cab = le_cabecalho(arq);

    if (cab->pos_cabeca == -1) {
        printf("A árvore está vazia.\n");
        return;
    }

    // Fila para armazenamento das posições dos nós nos níveis
    int fila[100];  // ajustar conforme necessário
    int inicio = 0, fim = 0;

    // Inserir a posição da raiz na fila
    fila[fim++] = cab->pos_cabeca;

    while (inicio < fim) {
        int tamanho_nivel = fim - inicio;
        
        // Para cada nó no nível atual, imprime todos na mesma linha
        for (int i = 0; i < tamanho_nivel; i++) {
            int posicao_atual = fila[inicio++];
            
            no = le_livro(arq, posicao_atual);

            // Imprime o código do livro (ou outro campo relevante) do nó atual
            printf("%d ", no->codigo);
                
            // Adicionar filhos à fila, se existirem
            if (no->esquerda != -1) fila[fim++] = no->esquerda;
            if (no->direita != -1) fila[fim++] = no->direita;

            free(no);
            
        }
        printf("\n"); // Nova linha para indicar mudança de nível
    }
}
//Descrição: Imprime as informações de um livro específico com base no código fornecido.
//Pré-condição: O arquivo deve estar aberto em modo de leitura. O código deve ser um valor válido para busca na árvore.
//Pós-condição: As informações do livro correspondente ao código são exibidas no console, se encontrado. Se o livro não for encontrado, uma mensagem de erro é exibida.
void imprime_arquivo_codigo(FILE *arq, int codigo) {
    cabecalho *cab = le_cabecalho(arq);
    int posicao_atual = cab->pos_cabeca;
    livro *l = NULL;

    while (posicao_atual != -1) {
        // Lê o livro na posição atual
        l = le_livro(arq, posicao_atual);

        // Verifica se o código do livro corresponde ao código procurado
        if (l->codigo == codigo) {
            imprimir_livro(l);
            free(l);
            free(cab);
            return;
        }

        // Navega na árvore binária com base no código do livro
        if (codigo < l->codigo) {
            posicao_atual = l->esquerda;
        } else {
            posicao_atual = l->direita;
        }

        free(l);
    }

    // Livro não encontrado
    printf("Livro com código %d nao encontrado.\n", codigo);
    free(cab);
}
//Descrição: Imprime os livros de um autor específico.
//Pré-condição: O arquivo deve estar aberto em modo de leitura.
//Pós-condição: Os livros do autor especificado são exibidos no console. Se nenhum livro for encontrado, uma mensagem é exibida.
void imprimir_arquivo_autor(FILE* arq, char nome_autor[]) {
    cabecalho *cab = le_cabecalho(arq);
    int posicao_raiz = cab->pos_cabeca;
    int encontrado = 0;

    free(cab);

    percorrer_arquivo_autor(arq, posicao_raiz, nome_autor, &encontrado);

    if (!encontrado)
        printf("Livro(s) do autor(a) %s nao encontrado\n", nome_autor);
}
//Descrição: Função auxiliar que percorre a árvore binária para encontrar e imprimir livros de um autor específico.
//Pré-condição: O arquivo deve estar aberto e acessível. pos_atual deve ser uma posição válida na árvore.
//Pós-condição: Os livros do autor especificado são impressos, se encontrados.
void percorrer_arquivo_autor(FILE* arq, int pos_atual, char nome_autor[], int* encontrado) {
    livro* l = NULL;

    l = le_livro(arq, pos_atual);

    if (strcmp(l->autor,nome_autor) == 0) {
        printf("Codigo: %d\n", l->codigo);
        printf("Titulo: %s\n", l->titulo);
        printf("----------------------------\n");
        *encontrado = 1;
    }

    if (l->esquerda != -1) {
        percorrer_arquivo_autor(arq, l->esquerda, nome_autor, encontrado);
    }

    if (l->direita != -1) {
        percorrer_arquivo_autor(arq, l->direita, nome_autor, encontrado);
    }

    free(l);
}
//Descrição: Imprime os livros com um título específico.
//Pré-condição: O arquivo deve estar aberto em modo de leitura.
//Pós-condição: Os livros com o título especificado são exibidos no console. Se nenhum livro for encontrado, uma mensagem é exibida.
void imprimir_arquivo_titulo(FILE* arq, char nome_titulo[]) {
    cabecalho *cab = le_cabecalho(arq);
    int posicao_raiz = cab->pos_cabeca;
    int encontrado = 0;

    free(cab);

    percorrer_arquivo_titulo(arq, posicao_raiz, nome_titulo, &encontrado);

    if (!encontrado)
        printf("Livro(s) com titulo %s nao encontrado\n", nome_titulo);
}
//Descrição: Função auxiliar que percorre a árvore binária para encontrar e imprimir livros com um título específico.
//Pré-condição: O arquivo deve estar aberto e acessível. pos_atual deve ser uma posição válida na árvore.
//Pós-condição: O livro com o título especificado é impresso, se encontrado.
void percorrer_arquivo_titulo(FILE* arq, int pos_atual, char nome_titulo[], int* encontrado) {
    livro* l = NULL;

    l = le_livro(arq, pos_atual);

    if (strcmp(l->titulo,nome_titulo) == 0) {
        imprimir_livro(l);
        *encontrado = 1;
    }

    if (l->esquerda != -1) {
        percorrer_arquivo_titulo(arq, l->esquerda, nome_titulo, encontrado);
    }

    if (l->direita != -1) {
        percorrer_arquivo_titulo(arq, l->direita, nome_titulo, encontrado);
    }

    free(l);
}
//Descrição: Conta a quantidade total de livros no arquivo binário.
//Pré-condição: O arquivo deve estar aberto em modo de leitura.
//Pós-condição: Retorna a quantidade total de livros no arquivo.
int contar_arquivo_quantidade(FILE* arqBin) {
    cabecalho* cab = le_cabecalho(arqBin);

    int qtd = cab->quantidade_livros;

    free(cab);
    return qtd;
}
//Descrição: Exibe todos os livros presentes na árvore binária.
//Pré-condição: O arquivo deve estar aberto e acessível. pos_atual deve ser uma posição válida na árvore.
//Pós-condição: Todos os livros na árvore são exibidos no console.
void exibir_livros(FILE *arq, int pos_atual) {
    if (pos_atual == -1) {
        return; // Caso base: chegou em um nó vazio
    }

    // Ler o livro da posição atual
    livro *livro_atual = le_livro(arq, pos_atual);
    if (livro_atual == NULL) {
        printf("Erro ao ler livro na posição %d\n", pos_atual);
        return;
    }

    // Percorre a subárvore esquerda
    exibir_livros(arq, livro_atual->esquerda);

    // Exibe o livro atual
    imprimir_livro(livro_atual);

    // Percorre a subárvore direita
    exibir_livros(arq, livro_atual->direita);

    // Libera a memória alocada para o livro
    free(livro_atual);
}
//Descrição: Mostra as posições dos registros livres no arquivo binário.
//Pré-condição: O arquivo deve estar aberto em modo de leitura.
//Pós-condição: As posições dos registros livres são exibidas no console. Se não houver registros livres, uma mensagem informando que nenhum livro foi encontrado é exibida.
void mostrar_registro_livre(FILE* arqBin) {
    cabecalho* cab = le_cabecalho(arqBin);
    livro* l = NULL;

    int pos_atual;

    printf ("%d %d %d\n", cab->pos_cabeca, cab->pos_topo, cab->pos_livre);
    
    if (cab->pos_livre == -1) {
        printf ("\nNenhum livro encontrado!\n");
        free(cab);
        return;
    }

    pos_atual = cab->pos_livre;

    while(pos_atual != -1) {
        printf ("%d ", pos_atual);
        
        l = le_livro(arqBin, pos_atual);

        pos_atual = l->esquerda;

        free(l);
    }

    printf("\n");

    free(cab);
}


// Descrição: Remove espaços em branco no início e no final de cada campo de um struct 'livro_auxiliar_str'.
// Pré-Condicao: O struct 'livro_auxiliar_str' deve estar corretamente preenchido.
// Pós-Condicao: Campos do struct 'livro_auxiliar_str' são retornados sem espaços em branco.
livro_auxiliar_str filtrar_espaco(livro_auxiliar_str aux) {
        ignorar_espaco(aux.codigo);
        ignorar_espaco(aux.titulo);
        ignorar_espaco(aux.autor);
        ignorar_espaco(aux.editora);
        ignorar_espaco(aux.edicao);
        ignorar_espaco(aux.ano);
        ignorar_espaco(aux.preco);
        ignorar_espaco(aux.estoque);

        return aux;
}

// Descrição: Converte uma string de preço para um float, substituindo vírgulas por pontos.
// Pré-Condicao: A string de entrada deve estar formatada corretamente como um número.
// Pós-Condicao: A string é convertida para float.
float converter_string_float (char preco_str[]) {
    for (int i = 0; i < strlen(preco_str); i++)
    {
        if (preco_str[i] == ',')
            preco_str[i] = '.';
    }

    return atof(preco_str);
}


// Descrição: Remove espaços em branco no início e no fim de uma string.
// Pré-Condicao: A string de entrada deve ser uma string válida e não nula.
// Pós-Condicao: A string é retornada com espaços em branco removidos.
char* ignorar_espaco(char *str) {
    char *inicio = str;
    char *fim;

    // Trim leading space
    while (isspace((unsigned char)*inicio)) inicio++;
    if (*inicio == 0) {  // All spaces?
        *str = '\0';    // Set string to empty
        return str;
    }

    // Trim trailing space
    fim = inicio + strlen(inicio) - 1;
    while (fim > inicio && isspace((unsigned char)*fim)) fim--;

    // Write new null terminator character
    fim[1] = '\0';

    // Move the trimmed string to the beginning of the original buffer
    if (inicio != str) {
        memmove(str, inicio, fim - inicio + 2); // +2 to include the '\0' character
    }

    return str;
}

// Descrição: Carrega os dados de um arquivo de texto e insere os registros no arquivo binário.
// Pré-Condicao: Ambos os arquivos devem estar abertos nos modos apropriados (texto para leitura, binário para escrita).
// Pós-Condicao: Dados do arquivo de texto são inseridos no arquivo binário.
void carregar_arquivo_para_binario(FILE* arqTxt, FILE* arqBin) {
    livro* nova_info = malloc(sizeof(livro));
    livro_auxiliar_str aux_info;


    int qtd = 0;

    while 
    (fscanf(arqTxt, "%[^;]%*c%[^;]%*c%[^;]%*c%[^;]%*c%[^;]%*c%[^;]%*c%[^;]%*c%[^\n]%*c",
    aux_info.codigo, aux_info.titulo, aux_info.autor, aux_info.editora, aux_info.edicao, 
    aux_info.ano, aux_info.preco, aux_info.estoque) != EOF) {
        aux_info = filtrar_espaco(aux_info);
        copiar_info_livro_str(nova_info, aux_info);
        imprimir_livro(nova_info);
        inserir_livro(arqBin, nova_info);

        qtd++;
    }
    
    cabecalho* cab = le_cabecalho(arqBin);

    cab->quantidade_livros = qtd;

    escreve_cabecalho(arqBin, cab);

    printf ("Arquivo carregado com sucesso\n");
    free(cab);
    free(nova_info);
}