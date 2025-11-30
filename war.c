/*
    ============================================================================
                        WAR ESTRUTURADO - NÍVEL AVENTUREIRO
    ============================================================================
    Objetivo:
    - Evoluir o projeto do nível novato adicionando o sistema de ATAQUE.
    - Utilizar alocação dinâmica de memória.
    - Criar a função atacar() com rolagem de dados (rand).
    - Atualizar as tropas e dono do território defensor.
    - Separar o código em funções organizadas.
    ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -----------------------------------------------------------------------------
// STRUCT TERRITÓRIO
// -----------------------------------------------------------------------------
typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

// -----------------------------------------------------------------------------
// PROTÓTIPOS
// -----------------------------------------------------------------------------
Territorio* criarMapa(int quantidade);
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
void limparBuffer();

// -----------------------------------------------------------------------------
// FUNÇÃO PRINCIPAL
// -----------------------------------------------------------------------------
int main() {
    srand(time(NULL)); // gerar valores aleatórios

    int quantidade;

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &quantidade);
    limparBuffer();

    Territorio* mapa = criarMapa(quantidade);

    if (!mapa) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, quantidade);

    int opcao;
    do {
        printf("\n============== MENU ==============\n");
        printf("1 - Exibir mapa\n");
        printf("2 - Realizar ataque\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao == 1) {
            exibirMapa(mapa, quantidade);
        }

        else if (opcao == 2) {
            exibirMapa(mapa, quantidade);

            int atk, def;

            printf("\nEscolha o ID do território ATACANTE: ");
            scanf("%d", &atk);
            limparBuffer();

            printf("Escolha o ID do território DEFENSOR: ");
            scanf("%d", &def);
            limparBuffer();

            if (atk < 0 || atk >= quantidade || def < 0 || def >= quantidade) {
                printf("IDs inválidos!\n");
                continue;
            }

            if (strcmp(mapa[atk].cor, mapa[def].cor) == 0) {
                printf("Erro: não é possível atacar um território da mesma cor.\n");
                continue;
            }

            atacar(&mapa[atk], &mapa[def]);

        }

    } while (opcao != 0);

    liberarMemoria(mapa);

    printf("\nJogo finalizado.\n");
    return 0;
}

// -----------------------------------------------------------------------------
// FUNÇÃO DE ALOCAÇÃO DINÂMICA
// -----------------------------------------------------------------------------
Territorio* criarMapa(int quantidade) {
    return (Territorio*)calloc(quantidade, sizeof(Territorio));
}

// -----------------------------------------------------------------------------
// CADASTRAR TERRITÓRIOS
// -----------------------------------------------------------------------------
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i);

        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Tropas iniciais: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();
    }
}

// -----------------------------------------------------------------------------
// EXIBIR O MAPA
// -----------------------------------------------------------------------------
void exibirMapa(Territorio* mapa, int quantidade) {
    printf("\n========== MAPA ATUAL ==========\n");

    for (int i = 0; i < quantidade; i++) {
        printf("\nID: %d\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }

    printf("\n================================\n");
}

// -----------------------------------------------------------------------------
// FUNÇÃO DE ATAQUE
// -----------------------------------------------------------------------------
void atacar(Territorio* atacante, Territorio* defensor) {

    if (atacante->tropas < 2) {
        printf("\nErro: O atacante não possui tropas suficientes.\n");
        return;
    }

    printf("\n=========== ATAQUE ===========\n");
    printf("%s (%s) ATACANDO %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("\nDado do ATACANTE: %d\n", dadoAtk);
    printf("Dado do DEFENSOR: %d\n", dadoDef);

    if (dadoAtk > dadoDef) {
        printf("\nTerritório CONQUISTADO!\n");

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas = atacante->tropas / 2;
    } else {
        printf("\nAtaque falhou! O atacante perdeu 1 tropa.\n");
        atacante->tropas -= 1;
    }

    printf("\n--- STATUS APÓS ATAQUE ---\n");
    printf("Atacante (%s): %d tropas\n", atacante->nome, atacante->tropas);
    printf("Defensor  (%s): %d tropas\n", defensor->nome, defensor->tropas);
    printf("================================\n");
}

// -----------------------------------------------------------------------------
// LIBERAR MEMÓRIA
// -----------------------------------------------------------------------------
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// -----------------------------------------------------------------------------
// LIMPAR BUFFER
// -----------------------------------------------------------------------------
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
