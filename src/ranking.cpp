#include <stdio.h>
#include <string.h>
#include "../header/ranking.h"
#include "../header/constante.h"

void inicializarRanking(Ranking* ranking) {
    if (!ranking) return;
    ranking->totalJogadores = 0;
    for (int i = 0; i < MAX_JOGADORES; i++) {
        ranking->jogadores[i].vidas = 0;
        ranking->jogadores[i].pontos = 0;
        ranking->jogadores[i].tempoJogado = 0;
        ranking->jogadores[i].nome[0] = '\0';
        ranking->jogadores[i].dataHora[0] = '\0';
    }
}

void adicionarJogadorRanking(Ranking* ranking, Jogador jogador) {
    if (!ranking || ranking->totalJogadores >= MAX_JOGADORES) return;
    ranking->jogadores[ranking->totalJogadores] = jogador;
    ranking->totalJogadores++;
    ordenarRanking(ranking);
}

void ordenarRanking(Ranking* ranking) {
    if (!ranking || ranking->totalJogadores <= 1) return;
    
    for (int i = 0; i < ranking->totalJogadores - 1; i++) {
        for (int j = 0; j < ranking->totalJogadores - i - 1; j++) {
            if (ranking->jogadores[j].pontos < ranking->jogadores[j + 1].pontos) {
                Jogador temp = ranking->jogadores[j];
                ranking->jogadores[j] = ranking->jogadores[j + 1];
                ranking->jogadores[j + 1] = temp;
            }
        }
    }
}

void salvarRanking(Ranking* ranking, const char* arquivo) {
    if (!ranking || !arquivo) return;
    
    FILE *f = fopen(arquivo, "w");
    if (!f) return;
    
    fprintf(f, "%d\n", ranking->totalJogadores);
    for (int i = 0; i < ranking->totalJogadores; i++) {
        fprintf(f, "%s|%d|%d|%s\n",
                ranking->jogadores[i].nome,
                ranking->jogadores[i].pontos,
                ranking->jogadores[i].tempoJogado,
                ranking->jogadores[i].dataHora);
    }
    
    fclose(f);
}

void carregarRanking(Ranking* ranking, const char* arquivo) {
    if (!ranking || !arquivo) return;
    
    inicializarRanking(ranking);
    
    FILE *f = fopen(arquivo, "r");
    if (!f) return;
    
    int total = 0;
    if (fscanf(f, "%d\n", &total) != 1) {
        fclose(f);
        return;
    }
    
    if (total > MAX_JOGADORES) total = MAX_JOGADORES;
    
    for (int i = 0; i < total; i++) {
        char buffer[200];
        if (fgets(buffer, sizeof(buffer), f) == NULL) break;
        
        char nome[50];
        int pontos, tempo;
        char dataHora[30];
        
        if (sscanf(buffer, "%49[^|]|%d|%d|%29[^\n]", nome, &pontos, &tempo, dataHora) == 4) {
            strncpy(ranking->jogadores[i].nome, nome, sizeof(ranking->jogadores[i].nome) - 1);
            ranking->jogadores[i].nome[sizeof(ranking->jogadores[i].nome) - 1] = '\0';
            ranking->jogadores[i].pontos = pontos;
            ranking->jogadores[i].tempoJogado = tempo;
            strncpy(ranking->jogadores[i].dataHora, dataHora, sizeof(ranking->jogadores[i].dataHora) - 1);
            ranking->jogadores[i].dataHora[sizeof(ranking->jogadores[i].dataHora) - 1] = '\0';
            ranking->totalJogadores++;
        }
    }
    
    fclose(f);
    ordenarRanking(ranking);
}

void desenharRanking(Ranking* ranking) {
    if (!ranking) return;
    
    printf("\n");
    printf("========================================\n");
    printf("           RANKING - TOP 10\n");
    printf("========================================\n");
    printf("Pos | Nome                | Pontos | Tempo\n");
    printf("----------------------------------------\n");
    
    int limite = ranking->totalJogadores < 10 ? ranking->totalJogadores : 10;
    
    for (int i = 0; i < limite; i++) {
        printf("%2d  | %-18s | %6d | %4ds\n",
               i + 1,
               ranking->jogadores[i].nome,
               ranking->jogadores[i].pontos,
               ranking->jogadores[i].tempoJogado);
    }
    
    printf("========================================\n\n");
}
