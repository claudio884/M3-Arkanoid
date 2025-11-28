#include "../header/bola.h"
#include "../header/constantes.h"
#include "raylib.h"
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846f
#endif

void normalizarVelocidade(Bola *bola, float velocidadeDesejada) {
    float velocidadeAtual = sqrtf(bola->velocidadeX * bola->velocidadeX + 
                                   bola->velocidadeY * bola->velocidadeY);
    if (velocidadeAtual > 0.001f) {
        bola->velocidadeX *= velocidadeDesejada / velocidadeAtual;
        bola->velocidadeY *= velocidadeDesejada / velocidadeAtual;
    }
}

void inicializarBola(Bola *bola, Barra *barra) {
    bola->raio = RADIO;
    bola->posicao.x = barra->posicao.x + barra->largura / 2.0f;
    bola->posicao.y = barra->posicao.y - bola->raio - 2.0f;
    bola->velocidadeX = 0.0f;
    bola->velocidadeY = 0.0f;
    bola->presa = true;
    bola->rastroIndex = 0;
    for (int i = 0; i < 10; i++) {
        bola->rastro[i].x = bola->posicao.x;
        bola->rastro[i].y = bola->posicao.y;
    }
}

void atualizarBola(Bola *bola, Barra *barra, float dt) {
    if (bola->presa) {
        bola->posicao.x = barra->posicao.x + barra->largura / 2.0f;
        bola->posicao.y = barra->posicao.y - bola->raio - 2.0f;
        return;
    }

    bola->rastro[bola->rastroIndex].x = bola->posicao.x;
    bola->rastro[bola->rastroIndex].y = bola->posicao.y;
    bola->rastroIndex = (bola->rastroIndex + 1) % 10;

    bola->posicao.x += bola->velocidadeX * dt;
    bola->posicao.y += bola->velocidadeY * dt;

    float velocidadeAtual = sqrtf(bola->velocidadeX * bola->velocidadeX + 
                                   bola->velocidadeY * bola->velocidadeY);
    
    if (bola->posicao.x - bola->raio < 0) {
        bola->posicao.x = bola->raio;
        bola->velocidadeX = fabsf(bola->velocidadeX);
        normalizarVelocidade(bola, velocidadeAtual);
        bola->rastro[bola->rastroIndex].x = bola->posicao.x;
        bola->rastro[bola->rastroIndex].y = bola->posicao.y;
    }
    if (bola->posicao.x + bola->raio > SCREEN_WIDTH) {
        bola->posicao.x = SCREEN_WIDTH - bola->raio;
        bola->velocidadeX = -fabsf(bola->velocidadeX);
        normalizarVelocidade(bola, velocidadeAtual);
        bola->rastro[bola->rastroIndex].x = bola->posicao.x;
        bola->rastro[bola->rastroIndex].y = bola->posicao.y;
    }
    if (bola->posicao.y - bola->raio < 0) {
        bola->posicao.y = bola->raio;
        bola->velocidadeY = fabsf(bola->velocidadeY);
        if (fabsf(bola->velocidadeY) < 50.0f) {
            bola->velocidadeY = 50.0f;
        }
        normalizarVelocidade(bola, velocidadeAtual);
        bola->rastro[bola->rastroIndex].x = bola->posicao.x;
        bola->rastro[bola->rastroIndex].y = bola->posicao.y;
    }
}

void desenharBola(Bola *bola) {
    if (!bola->presa) {
        for (int i = 0; i < 10; i++) {
            int idx = (bola->rastroIndex + i) % 10;
            float alpha = (float)i / 10.0f;
            DrawCircle((int)bola->rastro[idx].x, (int)bola->rastro[idx].y, 
                      bola->raio * (0.5f + alpha * 0.5f), 
                      Fade(RED, alpha * 0.5f));
        }
    }
    
    DrawCircle((int)bola->posicao.x, (int)bola->posicao.y, bola->raio, RED);
    DrawCircle((int)bola->posicao.x, (int)bola->posicao.y, bola->raio - 2, ORANGE);
}

void lancarBola(Bola *bola, float velocidadeBase) {
    if (bola->presa) {
        bola->presa = false;
        float angulo = -60.0f + (float)(GetRandomValue(0, 60));
        float anguloRad = angulo * PI / 180.0f;
        bola->velocidadeX = velocidadeBase * sin(anguloRad);
        bola->velocidadeY = -velocidadeBase * cos(anguloRad);
    }
}

bool verificarColisaoBarra(Bola *bola, Barra *barra) {
    if (bola->presa) return false;

    if (bola->posicao.x + bola->raio >= barra->posicao.x &&
        bola->posicao.x - bola->raio <= barra->posicao.x + barra->largura &&
        bola->posicao.y + bola->raio >= barra->posicao.y &&
        bola->posicao.y - bola->raio <= barra->posicao.y + barra->altura) {
        
        if (bola->velocidadeY > 0) {
            bola->posicao.y = barra->posicao.y - bola->raio;
            
            float posRelativa = (bola->posicao.x - barra->posicao.x) / barra->largura;
            
            float angulo;
            if (fabsf(posRelativa - 0.5f) < 0.05f) {
                angulo = 0.0f;
            } else {
                angulo = -75.0f + posRelativa * 150.0f;
            }
            
            float anguloRad = angulo * PI / 180.0f;
            float velocidade = sqrtf(bola->velocidadeX * bola->velocidadeX + 
                                     bola->velocidadeY * bola->velocidadeY);
            
            bola->velocidadeX = velocidade * sinf(anguloRad);
            bola->velocidadeY = -velocidade * cosf(anguloRad);
            
            if (fabsf(bola->velocidadeY) < 50.0f) {
                bola->velocidadeY = -50.0f;
            }
            
            normalizarVelocidade(bola, velocidade);
            
            return true;
        }
    }
    return false;
}

void resetarBola(Bola *bola, Barra *barra) {
    bola->posicao.x = barra->posicao.x + barra->largura / 2.0f;
    bola->posicao.y = barra->posicao.y - bola->raio - 2.0f;
    bola->velocidadeX = 0.0f;
    bola->velocidadeY = 0.0f;
    bola->presa = true;
}
