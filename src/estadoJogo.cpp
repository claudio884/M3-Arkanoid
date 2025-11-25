#include "../header/estadoJogo.h"

void inicializarEstado(EstadoJogo *estado) {
    estado->estadoAtual = ESTADO_MENU;
    estado->dificuldade = DIFICULDADE_MEDIO;
    estado->faseAtual = 0;
    estado->multiplicadorVelocidade = 1.0f;
    estado->multiplicadorPontos = 1.0f;
    estado->inversorPontos = false;
    estado->tempoInversor = 0;
    estado->tempoMultiplicador = 0;
}

void mudarEstado(EstadoJogo *estado, int novoEstado) {
    estado->estadoAtual = novoEstado;
}

void aplicarDificuldade(EstadoJogo *estado, int dificuldade) {
    estado->dificuldade = dificuldade;
    estado->multiplicadorVelocidade = obterMultiplicadorVelocidade(dificuldade);
}

float obterMultiplicadorVelocidade(int dificuldade) {
    if (dificuldade == DIFICULDADE_FACIL) return 0.9f;
    if (dificuldade == DIFICULDADE_MEDIO) return 1.0f;
    return 1.15f;
}
