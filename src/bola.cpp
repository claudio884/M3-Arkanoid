#include <math.h>
#include "../header/bola.h"
#include "../header/constante.h"

static void limitarPosicao(Bola *bola) {
    if (bola->posicao.x - bola->raio < 0) { bola->posicao.x = bola->raio; bola->velocidadeX *= -1; }
    if (bola->posicao.x + bola->raio > SCREEN_WIDTH) { bola->posicao.x = SCREEN_WIDTH - bola->raio; bola->velocidadeX *= -1; }
    if (bola->posicao.y - bola->raio < 0) { bola->posicao.y = bola->raio; bola->velocidadeY *= -1; }
}

void inicializaBola(Bola* bola, Barra* barra) {
    bola->raio = RADIO;
    bola->velocidadeX = 0;
    bola->velocidadeY = 0;
    bola->presa = true;
    bola->rastroBola = 0;
    for (int i=0;i<10;i++){ bola->rastro[i].x = -1000; bola->rastro[i].y = -1000; }
    resetaBola(bola, barra);
}

void resetaBola(Bola* bola, Barra* barra) {
    bola->posicao.x = barra->posicao.x + barra->largura/2.0f;
    bola->posicao.y = barra->posicao.y - bola->raio - 1.0f;
    bola->velocidadeX = 0;
    bola->velocidadeY = 0;
    bola->presa = true;
}

void lancaBola(Bola* bola, float velocidadeInicial) {
    if (!bola->presa) return;
    bola->presa = false;
    bola->velocidadeX = velocidadeInicial*0.6f;
    bola->velocidadeY = -velocidadeInicial;
}

bool verificaColisaoBolaBarra(const Bola* bola, const Barra* barra) {
    if (bola->posicao.y + bola->raio >= barra->posicao.y &&
        bola->posicao.y - bola->raio <= barra->posicao.y + barra->altura &&
        bola->posicao.x + bola->raio >= barra->posicao.x &&
        bola->posicao.x - bola->raio <= barra->posicao.x + barra->largura) {
        return true;
    }
    return false;
}

void atualizaBola(Bola* bola, Barra* barra, float deltaTime) {
    if (bola->presa) {
        bola->posicao.x = barra->posicao.x + barra->largura/2.0f;
        bola->posicao.y = barra->posicao.y - bola->raio - 1.0f;
        return;
    }

    bola->posicao.x += bola->velocidadeX * deltaTime;
    bola->posicao.y += bola->velocidadeY * deltaTime;

    limitarPosicao(bola);

    if (verificaColisaoBolaBarra(bola, barra) && bola->velocidadeY > 0) {
        float centroBarra = barra->posicao.x + barra->largura/2.0f;
        float distancia = (bola->posicao.x - centroBarra) / (barra->largura/2.0f);
        if (distancia < -1.0f) distancia = -1.0f; if (distancia > 1.0f) distancia = 1.0f;
        float velocidade = sqrtf(bola->velocidadeX*bola->velocidadeX + bola->velocidadeY*bola->velocidadeY);
        bola->velocidadeX = velocidade * distancia;
        bola->velocidadeY = -fabsf(velocidade * (1.0f - fabsf(distancia)));
    }

    if (bola->posicao.y - bola->raio > SCREEN_HEIGHT) {
        bola->presa = true;
    }

    bola->rastro[bola->rastroBola] = bola->posicao;
    bola->rastroBola = (bola->rastroBola + 1) % 10;
}

void desenhaBola(const Bola* bola) {
}
