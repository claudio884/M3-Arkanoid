#ifndef TIJOLO_H
#define TIJOLO_H

#include "barra.h"
#include "bola.h"

struct Tijolo {
    Posicao posicao;
    float largura;
    float altura;
    bool ativo;
    int vidaAtual;
};

void inicializaTijolo(Tijolo* tijolo, float x, float y, int vidaAtual);
void desenhaTijolo(const Tijolo* tijolo);
void destroiTijolo(Tijolo* tijolo);
void colisaoTijolo(Tijolo* tijolo, Bola* bola);

#endif