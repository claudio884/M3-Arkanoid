#include "../header/tijolo.h"
#include "../header/cores.h"
#include "../header/constantes.h"
#include "../header/fases.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

void inicializarTijolo(Tijolo *tijolo, float posicaoX, float posicaoY, int vida) {
    static bool seedInicializado = false;
    if (!seedInicializado) {
        srand(time(0));
        seedInicializado = true;
    }
    
    tijolo->posicao.x = posicaoX;
    tijolo->posicao.y = posicaoY;
    tijolo->vida = vida;
    tijolo->ativo = true;
    tijolo->largura = TIJOLO_LARGURA;
    tijolo->altura = TIJOLO_ALTURA;

    tijolo->corAleatoria = rand() % 12; // 12 variações por paleta
}

void desenharTijolo(Tijolo *tijolo) {
    if (!tijolo->ativo) return;

    Color cor;

    // ================================
    //   FASE 1 — FORJA DEMONÍACA 🔥⚒
    // ================================
    Color forjaVida1[] = { // metal incandescente fraco
        {255,180,80,255},{255,170,60,255},{255,160,40,255},{240,150,30,255},
        {220,130,20,255},{200,110,10,255},{180,90,0,255},{200,100,40,255},
        {220,120,50,255},{240,140,70,255},{255,200,110,255},{255,190,100,255}
    };
    Color forjaVida2[] = { // brasas fortes
        {255,70,30,255},{240,60,25,255},{220,50,20,255},{200,40,15,255},
        {180,30,10,255},{160,20,10,255},{150,25,20,255},{180,40,30,255},
        {200,50,40,255},{220,60,50,255},{230,70,60,255},{240,80,70,255}
    };
    Color forjaVida3[] = { // ferro quente escuro
        {120,40,40,255},{100,30,30,255},{80,20,20,255},{70,18,18,255},
        {60,14,14,255},{50,10,10,255},{90,35,35,255},{110,45,45,255},
        {130,55,55,255},{150,65,65,255},{100,25,25,255},{140,50,50,255}
    };

    // ================================
    //     FASE 2 — VULCÃO 🌋🔥
    // ================================
    Color vulcaoVida1[] = { // lava brilhante
        {255,120,0,255},{255,110,0,255},{255,100,0,255},{240,90,0,255},
        {255,130,20,255},{255,140,40,255},{255,150,60,255},{255,160,70,255},
        {255,170,90,255},{255,180,110,255},{255,200,140,255},{255,220,160,255}
    };
    Color vulcaoVida2[] = { // lava mais quente/vermelha
        {220,30,0,255},{200,25,0,255},{180,20,0,255},{160,18,0,255},
        {150,16,0,255},{140,14,0,255},{130,12,0,255},{120,10,0,255},
        {110,8,0,255},{100,6,0,255},{90,4,0,255},{80,3,0,255}
    };
    Color vulcaoVida3[] = { // rocha vulcânica
        {70,30,30,255},{60,25,25,255},{50,20,20,255},{40,15,15,255},
        {30,12,12,255},{25,10,10,255},{70,35,35,255},{90,45,45,255},
        {110,55,55,255},{130,65,65,255},{80,30,30,255},{100,40,40,255}
    };

    // ==========================================
    //   FASE 3 — ABISMO INFERNAL 💀🔥💙
    // ==========================================
    Color abismoVida1[] = { // azul espectral fraco
        {80,100,255,255},{70,90,240,255},{60,80,220,255},{50,70,200,255},
        {40,60,180,255},{30,50,160,255},{20,40,140,255},{50,70,160,255},
        {70,90,180,255},{90,110,200,255},{110,130,220,255},{130,150,240,255}
    };
    Color abismoVida2[] = { // chamas azuis
        {30,0,200,255},{35,0,180,255},{40,0,160,255},{45,0,140,255},
        {50,0,120,255},{60,0,110,255},{70,0,130,255},{80,0,150,255},
        {90,0,170,255},{100,0,190,255},{120,0,220,255},{150,0,255,255}
    };
    Color abismoVida3[] = { // roxo demoníaco
        {70,0,90,255},{60,0,80,255},{50,0,70,255},{40,0,60,255},
        {30,0,50,255},{50,0,80,255},{70,0,110,255},{90,0,130,255},
        {110,0,150,255},{130,0,170,255},{150,0,190,255},{170,0,210,255}
    };

    // ========= Selecionar paleta por fase =========
    if (FASE_ATUAL == 1) {
        cor = (tijolo->vida >= 3) ? forjaVida3[tijolo->corAleatoria]
             : (tijolo->vida == 2) ? forjaVida2[tijolo->corAleatoria]
             :                      forjaVida1[tijolo->corAleatoria];
    }
    else if (FASE_ATUAL == 2) {
        cor = (tijolo->vida >= 3) ? vulcaoVida3[tijolo->corAleatoria]
             : (tijolo->vida == 2) ? vulcaoVida2[tijolo->corAleatoria]
             :                      vulcaoVida1[tijolo->corAleatoria];
    }
    else { // FASE 3 — ABISMO
        cor = (tijolo->vida >= 3) ? abismoVida3[tijolo->corAleatoria]
             : (tijolo->vida == 2) ? abismoVida2[tijolo->corAleatoria]
             :                      abismoVida1[tijolo->corAleatoria];
    }

    DrawRectangle(
        (int)tijolo->posicao.x,
        (int)tijolo->posicao.y,
        (int)tijolo->largura,
        (int)tijolo->altura,
        cor
    );

    DrawRectangleLines(
        (int)tijolo->posicao.x,
        (int)tijolo->posicao.y,
        (int)tijolo->largura,
        (int)tijolo->altura,
        BLACK
    );
}

bool verificarColisaoTijolo(Bola *bola, Tijolo *tijolo) {
    if (!tijolo->ativo) return false;

    float closestX = fmax(tijolo->posicao.x, fmin(bola->posicao.x, 
                          tijolo->posicao.x + tijolo->largura));
    float closestY = fmax(tijolo->posicao.y, fmin(bola->posicao.y, 
                          tijolo->posicao.y + tijolo->altura));

    float distanciaX = bola->posicao.x - closestX;
    float distanciaY = bola->posicao.y - closestY;
    float distanciaQuadrada = distanciaX * distanciaX + distanciaY * distanciaY;

    if (distanciaQuadrada < bola->raio * bola->raio) {

        float centroX = tijolo->posicao.x + tijolo->largura / 2.0f;
        float centroY = tijolo->posicao.y + tijolo->altura / 2.0f;

        float dx = bola->posicao.x - centroX;
        float dy = bola->posicao.y - centroY;

        float larguraMetade = tijolo->largura / 2.0f;
        float alturaMetade = tijolo->altura / 2.0f;

        float overlapX = larguraMetade + bola->raio - fabsf(dx);
        float overlapY = alturaMetade + bola->raio - fabsf(dy);

        float velocidadeAtual = sqrtf(bola->velocidadeX * bola->velocidadeX +
                                      bola->velocidadeY * bola->velocidadeY);

        if (overlapX < overlapY) {
            if (dx > 0) {
                bola->posicao.x = tijolo->posicao.x + tijolo->largura + bola->raio;
            } else {
                bola->posicao.x = tijolo->posicao.x - bola->raio;
            }
            bola->velocidadeX = -bola->velocidadeX;
        } else {
            if (dy > 0) {
                bola->posicao.y = tijolo->posicao.y + tijolo->altura + bola->raio;
            } else {
                bola->posicao.y = tijolo->posicao.y - bola->raio;
            }
            bola->velocidadeY = -bola->velocidadeY;

            if (fabsf(bola->velocidadeY) < 50.0f) {
                bola->velocidadeY = (bola->velocidadeY > 0) ? 50.0f : -50.0f;
            }
        }

        if (velocidadeAtual > 0.001f) {
            float novaVelocidade = sqrtf(
                bola->velocidadeX * bola->velocidadeX +
                bola->velocidadeY * bola->velocidadeY
            );
            if (novaVelocidade > 0.001f) {
                bola->velocidadeX *= velocidadeAtual / novaVelocidade;
                bola->velocidadeY *= velocidadeAtual / novaVelocidade;
            }
        }

        return true;
    }

    return false;
}

void danificarTijolo(Tijolo *tijolo) {
    if (tijolo->ativo) {
        tijolo->vida--;
        if (tijolo->vida <= 0) {
            tijolo->ativo = false;
        }
    }
}
