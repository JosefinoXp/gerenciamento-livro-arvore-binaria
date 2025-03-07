# 📚 Gerenciador de Biblioteca

Este projeto tem como objetivo o gerenciamento de uma biblioteca utilizando uma estrutura de **Árvore Binária** armazenada em um **arquivo binário**. O sistema permite operações como cadastro, busca e remoção de livros de maneira eficiente.

## 🚀 Funcionalidades

- 📖 Adicionar novos livros ao catálogo
- ❌ Remover livros cadastrados
- 🔍 Buscar livros pelo título, autor ou código
- 📋 Listar todos os livros cadastrados em ordem
- 💾 Armazenamento eficiente utilizando arquivos binários

## 🛠 Tecnologias Utilizadas

- **Linguagem:** C
- **Estrutura de Dados:** Árvore Binária
- **Manipulação de Arquivos:** Arquivo Binário

## 📁 Estrutura do Projeto

```
📂 Trabalho
│-- 📂 src           # Código-fonte principal
│   │-- arquivo.c       # Manipulação dos livros em binário
│   │-- arquivo.h      # Implementação das funções
│   │-- arquivo_teste.txt # Arquivo teste com livros prontos
│   │-- cabecalho.c     # Implementação das funções  
│   │-- cabecalho.h     # Manipulação cabecalho de binário
│   │-- livro.h    # Definições de livro
│   │-- livro.c    # Implementação das funções
│   │-- menu.h # Menu do powershell
│   │-- menu.c    # Implementação do menu
│   │-- main.c    # Chamada de menu
│-- README.md        # arquivo de documentação
│-- README_Trabalho2_AED.pdf  # arquivo de documentação
```

## 📌 Como Executar

1. **Clone este repositório:**
   ```sh
   git clone https://github.com/JosefinoXp/gerenciamento-livro-arvore-binaria
   ```
2. **Compile o projeto:**
   ```sh
   gcc src/main.c src/biblioteca.c src/arquivo.c -o biblioteca -Wall
   ```
3. **Execute o programa:**
   ```sh
   ./biblioteca
   ```
