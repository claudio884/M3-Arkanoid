#include <stdlib.h>
#include "../header/particulas.h"

void inicializarSistemaParticulas(SistemaParticulas *sistema) {
    sistema->quantidade = 200;
    for (int i=0;i<sistema->quantidade;i++) {
        sistema->particulas[i].ativa = false;
        sistema->particulas[i].vida = 0;
        sistema->particulas[i].vidaMaxima = 0;
        sistema->particulas[i].x = 0;
        sistema->particulas[i].y = 0;
        sistema->particulas[i].velocidadeX = 0;
        sistema->particulas[i].velocidadeY = 0;
        sistema->particulas[i].cor = (Color){255, 255, 255, 255};
    }
}

void criarExplosao(SistemaParticulas *sistema, float x, float y, Color cor, int quantidade) {
    int criadas = 0;
    for (int i=0;i<sistema->quantidade && criadas<quantidade;i++) {
        if (!sistema->particulas[i].ativa) {
            sistema->particulas[i].ativa = true;
            sistema->particulas[i].x = x;
            sistema->particulas[i].y = y;
            sistema->particulas[i].velocidadeX = ((float)((rand() % 200) - 100));
            sistema->particulas[i].velocidadeY = ((float)((rand() % 150) - 150));
            sistema->particulas[i].vidaMaxima = (float)((rand() % 25) + 20) / 10.0f;
            sistema->particulas[i].vida = sistema->particulas[i].vidaMaxima;
            sistema->particulas[i].cor = cor;
            criadas++;
        }
    }
}

void atualizarParticulas(SistemaParticulas *sistema, float dt) {
    for (int i=0;i<sistema->quantidade;i++) {
        if (!sistema->particulas[i].ativa) continue;
        sistema->particulas[i].vida -= dt;
        if (sistema->particulas[i].vida <= 0) { sistema->particulas[i].ativa = false; continue; }
        sistema->particulas[i].x += sistema->particulas[i].velocidadeX * dt;
        sistema->particulas[i].y += sistema->particulas[i].velocidadeY * dt;
        sistema->particulas[i].velocidadeY += 200.0f * dt;
    }
}

void desenharParticulas(SistemaParticulas *sistema) {
}
