#ifndef JOGADOR_H
#define JOGADOR_H

struct Jogador {
    char nome[50];
    char data[20];
    int pontuacao;
    int tempoJogado;
    int vidas;
};

void inicializarJogador(Jogador *jogador, const char *nome);

void atualizarPontuacao(Jogador *jogador, int pontos);

void adicionarVida(Jogador *jogador);

void removerVida(Jogador *jogador);

void atualizarTempo(Jogador *jogador, int segundos);

#endif
