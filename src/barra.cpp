#include "../header/constante.h"
#include "../header/barra.h"

void inicializaBarra(Barra* barraX) {
    barraX->posicao.x = SCREEN_WIDTH/2.0f - RECT_WIDTH/2.0f;
    barraX->posicao.y = SCREEN_HEIGHT - 60.0f;
    barraX->largura = RECT_WIDTH;
    barraX->altura = RECT_HEIGHT;
    barraX->velocidadeX = SPEED;
}

void atualizaBarra(Barra* barraX) {
    float delta = 0.016f;
    float movimento = 0.0f;
    if (movimento < 0) movimento -= 1.0f;
    if (movimento > 0) movimento += 1.0f;
    barraX->posicao.x += movimento * barraX->velocidadeX * delta;
    if (barraX->posicao.x < 0) barraX->posicao.x = 0;
    if (barraX->posicao.x + barraX->largura > SCREEN_WIDTH) barraX->posicao.x = SCREEN_WIDTH - barraX->largura;
}

void desenhaBarra(const Barra* barraX) {
}

void modificarTamanhoBarra(Barra* barraX, float tamanhoDelta) {
    float centro = barraX->posicao.x + barraX->largura/2.0f;
    barraX->largura += tamanhoDelta;
    if (barraX->largura < 40.0f) barraX->largura = 40.0f;
    if (barraX->largura > 240.0f) barraX->largura = 240.0f;
    barraX->posicao.x = centro - barraX->largura/2.0f;
    if (barraX->posicao.x < 0) barraX->posicao.x = 0;
    if (barraX->posicao.x + barraX->largura > SCREEN_WIDTH) barraX->posicao.x = SCREEN_WIDTH - barraX->largura;
}

