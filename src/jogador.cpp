#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../header/jogador.h"
#include "../header/constante.h"

void inicializaJogador(Jogador* jogador, const char* nome) {
    jogador->vidas = VIDAS_INICIAIS;
    jogador->pontos = 0;
    jogador->tempoJogado = 0;
    strncpy(jogador->nome, nome ? nome : "Anonimo", sizeof(jogador->nome)-1);
    jogador->nome[sizeof(jogador->nome)-1] = '\0';
    time_t agora = time(NULL);
    struct tm *tm_ = localtime(&agora);
    strftime(jogador->dataHora, sizeof(jogador->dataHora), "%Y-%m-%d %H:%M:%S", tm_);
}

void modificaPontos(Jogador* jogador, int pontosDelta) {
    jogador->pontos += pontosDelta;
    if (jogador->pontos < 0) jogador->pontos = 0;
}

void modificaVidas(Jogador* jogador, int vidasDelta) {
    jogador->vidas += vidasDelta;
    if (jogador->vidas < 0) jogador->vidas = 0;
}

void modificaTempoJogado(Jogador* jogador, int tempoDelta) {
    jogador->tempoJogado += tempoDelta;
    if (jogador->tempoJogado < 0) jogador->tempoJogado = 0;
}
