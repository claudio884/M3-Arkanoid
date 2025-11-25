#ifndef RANKING_H
#define RANKING_H

#include "jogador.h"
#include "constante.h"

struct Ranking{
    Jogador jogadores[MAX_JOGADORES];
    int totalJogadores;
};

void inicializarRanking(Ranking* ranking);
void adicionarJogadorRanking(Ranking* ranking, Jogador jogador);
void ordenarRanking(Ranking* ranking);
void salvarRanking(Ranking* ranking, const char* arquivo);
void carregarRanking(Ranking* ranking, const char* arquivo);
void desenharRanking(Ranking* ranking);
#endif