/*
    ============================================================================
                        WAR ESTRUTURADO - NÍVEL NOVATO
    ============================================================================
    Objetivo:
    - Criar uma struct Territorio
    - Criar um vetor ESTÁTICO com 5 territórios
    - Permitir o cadastro de Nome, Cor e Tropas
    - Exibir o mapa completo

    Conceitos:
    - struct
    - vetor estático
    - scanf, fgets, printf
    ============================================================================
*/

#include <stdio.h>
#include <string.h>

// -----------------------------------------------------------------------------
// Struct Territorio
// -----------------------------------------------------------------------------
typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

// -----------------------------------------------------------------------------
// Função para limpar o buffer
// -----------------------------------------------------------------------------
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// -----------------------------------------------------------------------------
// Função para cadastrar os territórios
// -----------------------------------------------------------------------------
void cadastrarTerritorios(Territorio mapa[5]) {
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
    }
}

// -----------------------------------------------------------------------------
// Função para exibir o mapa
// -----------------------------------------------------------------------------
void exibirMapa(Territorio mapa[5]) {
    printf("\n==================== MAPA ATUAL ====================\n");

    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }

    printf("====================================================\n");
}

// -----------------------------------------------------------------------------
// Função Principal
// -----------------------------------------------------------------------------
int main() {
    Territorio mapa[5]; // vetor ESTÁTICO de 5 territórios

    printf("=== Cadastro Inicial dos Territórios (Nível Novato) ===\n");

    cadastrarTerritorios(mapa);
    exibirMapa(mapa);

    return 0;
}
