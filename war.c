/*
    ============================================================================
                        WAR ESTRUTURADO - NÍVEL MESTRE
    ============================================================================
    Objetivo:
    - Modularização total do programa WAR.
    - Sistema completo de missões e verificação de vitória.
    - Uso adequado de ponteiros, const correctness e boas práticas.
    - Menu com opções: Atacar, Verificar Missão e Sair.
    ============================================================================    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================================================
// ESTRUTURA DO TERRITÓRIO
// ============================================================================
typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

// ============================================================================
// PROTÓTIPOS
// ============================================================================
void inicializarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(const Territorio* mapa, int quantidade);

void atacar(Territorio* atacante, Territorio* defensor);
void limparBuffer();

int sortearMissao();
void exibirMissao(int idMissao);
int verificarVitoria(int idMissao, const Territorio* mapa, int quantidade, const char* corJogador);

Territorio* criarMapa(int quantidade);
void liberarMapa(Territorio* mapa);

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================
int main() {
    srand(time(NULL));

    const int quantidade = 5;        // Agora o mestre define os territórios automaticamente
    const char corJogador[15] = "Azul";

    Territorio* mapa = criarMapa(quantidade);

    if (!mapa) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    inicializarTerritorios(mapa, quantidade);

    int missao = sortearMissao();

    int opcao;
    do {
        printf("\n================= MENU PRINCIPAL =================\n");
        printf("Jogador: %s\n", corJogador);
        exibirMissao(missao);

        printf("\n1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao == 1) {
            exibirMapa(mapa, quantidade);

            int atk, def;
            printf("\nID do território ATACANTE: ");
            scanf("%d", &atk);
            limparBuffer();
            printf("ID do território DEFENSOR: ");
            scanf("%d", &def);
            limparBuffer();

            if (atk < 0 || atk >= quantidade || def < 0 || def >= quantidade) {
                printf("IDs inválidos!\n");
                continue;
            }

            if (strcmp(mapa[atk].cor, corJogador) != 0) {
                printf("Você só pode atacar com um território de sua cor (%s)!\n", corJogador);
                continue;
            }

            if (strcmp(mapa[def].cor, corJogador) == 0) {
                printf("Você não pode atacar um território aliado!\n");
                continue;
            }

            atacar(&mapa[atk], &mapa[def]);
        }

        else if (opcao == 2) {
            if (verificarVitoria(missao, mapa, quantidade, corJogador)) {
                printf("\n🎉 PARABÉNS! VOCÊ COMPLETOU SUA MISSÃO! 🎉\n");
                exibirMapa(mapa, quantidade);
                break;
            } else {
                printf("\n🚫 Missão AINDA não concluída. Continue lutando!\n");
            }
        }

    } while (opcao != 0);

    liberarMapa(mapa);
    printf("\nJogo encerrado.\n");
    return 0;
}

// ============================================================================
// INICIALIZAÇÃO AUTOMÁTICA DOS TERRITÓRIOS
// ============================================================================
void inicializarTerritorios(Territorio* mapa, int quantidade) {
    const char* nomes[] = {"Alaska", "China", "Brasil", "Egito", "Japão"};
    const char* cores[] = {"Vermelho", "Verde", "Amarelo", "Azul", "Preto"};
    const int tropas[] = {5, 3, 4, 6, 5};

    for (int i = 0; i < quantidade; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = tropas[i];
    }
}

// ============================================================================
// EXIBIR MAPA
// ============================================================================
void exibirMapa(const Territorio* mapa, int quantidade) {
    printf("\n================== MAPA ATUAL ==================\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nID %d\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
    printf("\n================================================\n");
}

// ============================================================================
// ATAQUE
// ============================================================================
void atacar(Territorio* atacante, Territorio* defensor) {

    if (atacante->tropas < 2) {
        printf("\nErro: o atacante não possui tropas suficientes.\n");
        return;
    }

    printf("\n============= ATAQUE =============\n");
    printf("%s (%s) ATACANDO %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Dado Atacante: %d\n", dadoAtk);
    printf("Dado Defensor: %d\n", dadoDef);

    if (dadoAtk > dadoDef) {
        printf("Território CONQUISTADO!\n");

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
    } else {
        printf("Ataque falhou! Atacante perde 1 tropa.\n");
        atacante->tropas--;
    }
}

// ============================================================================
// MISSÕES
// ============================================================================
int sortearMissao() {
    return (rand() % 2) + 1; // 1 ou 2
}

void exibirMissao(int idMissao) {
    printf("\n--- SUA MISSÃO ---\n");
    if (idMissao == 1)
        printf("1) Destruir o exército Verde\n");
    else
        printf("2) Conquistar 3 territórios\n");
}

// ============================================================================
// VERIFICAÇÃO DE VITÓRIA
// ============================================================================
int verificarVitoria(int idMissao, const Territorio* mapa, int quantidade, const char* corJogador) {

    if (idMissao == 1) {
        // Missão: destruir Verde
        for (int i = 0; i < quantidade; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0) {
                return 0; // Verde ainda existe
            }
        }
        return 1; // vitória
    }

    if (idMissao == 2) {
        // Missão: conquistar 3 territórios
        int contador = 0;
        for (int i = 0; i < quantidade; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0)
                contador++;
        }
        return (contador >= 3);  
    }

    return 0;
}

// ============================================================================
// MEMÓRIA
// ============================================================================
Territorio* criarMapa(int quantidade) {
    return (Territorio*)calloc(quantidade, sizeof(Territorio));
}

void liberarMapa(Territorio* mapa) {
    free(mapa);
}

// ============================================================================
// LIMPAR BUFFER
// ============================================================================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
