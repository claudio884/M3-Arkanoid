#ifndef PARTICULAS_H
#define PARTICULAS_H

#include "raylib.h"

struct Particula {
    float x;
    float y;
    float velocidadeX;
    float velocidadeY;
    float vida;
    float vidaMaxima;
    Color cor;
    bool ativa;
};

struct SistemaParticulas {
    Particula particulas[200];
    int quantidade;
};

void inicializarSistemaParticulas(SistemaParticulas *sistema);

void criarExplosao(SistemaParticulas *sistema, float x, float y, Color cor, int quantidade);

void atualizarParticulas(SistemaParticulas *sistema, float dt);

void desenharParticulas(SistemaParticulas *sistema);

#endif
