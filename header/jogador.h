#ifndef JOGADOR_H
#define JOGADOR_H

#include "barra.h"

struct Jogador {
    int vidas;
    int pontos;
    int tempoJogado;
    char dataHora[30];
    char nome[50];
};

void inicializaJogador(Jogador* jogador, const char* nome);
void modificaPontos(Jogador* jogador, int pontosDelta);
void modificaVidas(Jogador* jogador, int vidasDelta);
void modificaTempoJogado(Jogador* jogador, int tempoDelta);

#endif