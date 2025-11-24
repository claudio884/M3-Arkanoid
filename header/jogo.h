#ifndef JOGO_H
#define JOGO_H

#include "barra.h"
#include "bola.h"
#include "fase.h"
#include "jogador.h"
#include "item.h"
#include "estadoJogo.h"
#include "sons.h"
#include "particulas.h"
#include "constante.h"

struct Jogo {
    Barra barra;
    Bola bola;
    Fase fase;
    Jogador jogador;
    EstadoJogo estado;
    Item itens[MAX_ITENS];
    int qtdItens;
    Sons sons;
    SistemaParticulas particulas;
    float tempoInicio;
    float tempoDecorrido;
    float shakeX;
    float shakeY;
    float shakeIntensidade;
};

void inicializarJogo(Jogo *jogo, const char *nomeJogador, int dificuldade);

void atualizarJogo(Jogo *jogo, float dt);

void desenharJogo(Jogo *jogo);

void processarColisoes(Jogo *jogo);

void gerarItem(Jogo *jogo, Posicao posicao);

void aplicarEfeitoItem(Jogo *jogo, int tipoItem);

void proximaFase(Jogo *jogo);

void reiniciarJogo(Jogo *jogo);

void finalizarJogo(Jogo *jogo);

#endif