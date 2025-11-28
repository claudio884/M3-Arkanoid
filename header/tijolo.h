#ifndef TIJOLO_H
#define TIJOLO_H

#include "barra.h"
#include "bola.h"

struct Tijolo {
    Posicao posicao;
    int vida;
    bool ativo;
    float largura;
    float altura;
    int corAleatoria;
};

void inicializarTijolo(Tijolo *tijolo, float posicaoX, float posicaoY, int vida);

void desenharTijolo(Tijolo *tijolo);

bool verificarColisaoTijolo(Bola *bola, Tijolo *tijolo);

void danificarTijolo(Tijolo *tijolo);

#endif
