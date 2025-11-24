#ifndef ESTADO_H
#define ESTADO_H

#define ESTADO_MENU 0
#define ESTADO_JOGO 1
#define ESTADO_RANKING 2
#define ESTADO_DIFICULDADE 3
#define ESTADO_GAME_OVER 4
#define ESTADO_VITORIA 5
#define ESTADO_PAUSA 6
#define ESTADO_REGISTRO 7

#define DIFICULDADE_FACIL 0
#define DIFICULDADE_MEDIO 1
#define DIFICULDADE_DIFICIL 2

#define TIPO_ITEM_VIDA 0
#define TIPO_ITEM_AUMENTAR_BARRA 1
#define TIPO_ITEM_DIMINUIR_BARRA 2
#define TIPO_ITEM_PONTOS_EXTRA 3
#define TIPO_ITEM_MULTIPLICADOR 4
#define TIPO_ITEM_INVERSOR 5

#define MAX_ITENS 50
#define MAX_FASES 3

struct EstadoJogo {
    int estadoAtual;
    int dificuldade;
    int faseAtual;
    float multiplicadorVelocidade;
    float multiplicadorPontos;
    bool inversorPontos;
    int tempoInversor;
    int tempoMultiplicador;
};

void inicializarEstado(EstadoJogo *estado);

void mudarEstado(EstadoJogo *estado, int novoEstado);

void aplicarDificuldade(EstadoJogo *estado, int dificuldade);

float obterMultiplicadorVelocidade(int dificuldade);

#endif
