#include "../header/particulas.h"
#include "raylib.h"
#include <cmath>

void inicializarSistemaParticulas(SistemaParticulas *sistema) {
    sistema->quantidade = 0;
    for (int i = 0; i < 200; i++) {
        sistema->particulas[i].ativa = false;
    }
}

void criarExplosao(SistemaParticulas *sistema, float x, float y, Color cor, int quantidade) {
    for (int i = 0; i < quantidade && sistema->quantidade < 200; i++) {
        for (int j = 0; j < 200; j++) {
            if (!sistema->particulas[j].ativa) {
                float angulo = (float)(GetRandomValue(0, 360)) * 0.017453f;
                float velocidade = (float)(GetRandomValue(50, 150));
                
                sistema->particulas[j].x = x;
                sistema->particulas[j].y = y;
                sistema->particulas[j].velocidadeX = cosf(angulo) * velocidade;
                sistema->particulas[j].velocidadeY = sinf(angulo) * velocidade;
                sistema->particulas[j].vida = 1.0f;
                sistema->particulas[j].vidaMaxima = 1.0f;
                sistema->particulas[j].cor = cor;
                sistema->particulas[j].ativa = true;
                sistema->quantidade++;
                break;
            }
        }
    }
}

void atualizarParticulas(SistemaParticulas *sistema, float dt) {
    for (int i = 0; i < 200; i++) {
        if (sistema->particulas[i].ativa) {
            sistema->particulas[i].x += sistema->particulas[i].velocidadeX * dt;
            sistema->particulas[i].y += sistema->particulas[i].velocidadeY * dt;
            sistema->particulas[i].velocidadeY += 300.0f * dt;
            sistema->particulas[i].vida -= dt * 2.0f;
            
            if (sistema->particulas[i].vida <= 0.0f) {
                sistema->particulas[i].ativa = false;
                sistema->quantidade--;
            }
        }
    }
}

void desenharParticulas(SistemaParticulas *sistema) {
    for (int i = 0; i < 200; i++) {
        if (sistema->particulas[i].ativa) {
            float proporcao = sistema->particulas[i].vida / sistema->particulas[i].vidaMaxima;
            
            Color cor = sistema->particulas[i].cor;

            cor.a = (unsigned char)(255 * proporcao);
            
            float tamanho = 3.0f + (1.0f - proporcao) * 2.0f;
            DrawCircle((int)sistema->particulas[i].x, (int)sistema->particulas[i].y, tamanho, cor);
        }
    }
}
