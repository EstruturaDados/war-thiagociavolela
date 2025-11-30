/*
    ---------------------------------------------------------------
    SISTEMA DE CADASTRO DE LIVROS — NÍVEL NOVATO
    Estruturas de Dados (Structs, Vetores e Encapsulamento)
    ---------------------------------------------------------------

    Aluno: Thiago Ciavolela Brito de Oliveira
    Projeto: Nível Novato — Conhecendo as Estruturas de Dados

    Descrição:
    Este programa implementa um sistema simples de cadastro de livros
    utilizando estruturas de dados do tipo struct e um vetor linear.
    O usuário informa quantos livros deseja cadastrar e, a partir disso,
    o sistema solicita os dados de cada livro (nome, autor, editora e
    edição). Todas as informações são armazenadas em um vetor de structs,
    demonstrando organização, encapsulamento e manipulação básica de
    dados em memória.

    Conceitos Aplicados:
    - Estruturas de dados lineares (vetor)
    - Uso de struct para encapsulamento de informações
    - Entrada e saída de dados
    - Manipulação de strings
    - Alocação dinâmica com malloc()
    - Limpeza de buffer
    - Organização modular com funções em C

    ---------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------
   Struct Livro
   Representa uma entidade “Livro”, agrupando seus dados
------------------------------------------------------------- */
typedef struct {
    char nome[100];
    char autor[100];
    char editora[100];
    int edicao;
} Livro;

/* -------------------------------------------------------------
   Função: cadastrarLivros
   Objetivo: Receber os dados informados pelo usuário e
   armazená-los no vetor de structs.
------------------------------------------------------------- */
void cadastrarLivros(Livro *livros, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Cadastro do Livro %d ---\n", i + 1);

        printf("Nome do livro: ");
        fgets(livros[i].nome, sizeof(livros[i].nome), stdin);
        livros[i].nome[strcspn(livros[i].nome, "\n")] = '\0';

        printf("Autor: ");
        fgets(livros[i].autor, sizeof(livros[i].autor), stdin);
        livros[i].autor[strcspn(livros[i].autor, "\n")] = '\0';

        printf("Editora: ");
        fgets(livros[i].editora, sizeof(livros[i].editora), stdin);
        livros[i].editora[strcspn(livros[i].editora, "\n")] = '\0';

        printf("Número da edição: ");
        scanf("%d", &livros[i].edicao);
        getchar(); // limpeza do buffer
    }
}

/* -------------------------------------------------------------
   Função: exibirLivros
   Objetivo: Mostrar todos os livros cadastrados pelo usuário.
------------------------------------------------------------- */
void exibirLivros(Livro *livros, int quantidade) {
    printf("\n==============================\n");
    printf("     LIVROS CADASTRADOS\n");
    printf("==============================\n");

    for (int i = 0; i < quantidade; i++) {
        printf("\nLivro %d:\n", i + 1);
        printf("Nome: %s\n", livros[i].nome);
        printf("Autor: %s\n", livros[i].autor);
        printf("Editora: %s\n", livros[i].editora);
        printf("Edição: %d\n", livros[i].edicao);
    }
}

/* -------------------------------------------------------------
   Função Principal
   Responsável pelo fluxo geral do programa.
------------------------------------------------------------- */
int main() {
    int quantidade;

    printf("Quantos livros deseja cadastrar? ");
    scanf("%d", &quantidade);
    getchar(); // limpa o \n deixado pelo scanf

    // Alocação dinâmica do vetor de structs
    Livro *livros = (Livro *)malloc(quantidade * sizeof(Livro));

    if (livros == NULL) {
        printf("Erro ao alocar memória. Encerrando o sistema.\n");
        return 1;
    }

    cadastrarLivros(livros, quantidade);
    exibirLivros(livros, quantidade);

    free(livros); // Liberação da memória alocada

    printf("\nPrograma finalizado com sucesso.\n");
    return 0;
}
