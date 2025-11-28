#include "../header/barra.h"
#include "../header/constantes.h"
#include "../header/utils.h"
#include "raylib.h"

void inicializarBarra(Barra *barra) {
    barra->posicao.x = SCREEN_WIDTH / 2.0f - RECT_WIDTH / 2.0f;
    barra->posicao.y = SCREEN_HEIGTH - 50.0f;
    barra->largura = RECT_WIDTH;
    barra->altura = RECT_HEIGTH;
    barra->velocidadeX = 0.0f;
}

void atualizarBarra(Barra *barra, float dt) {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        barra->velocidadeX = -SPEED;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        barra->velocidadeX = SPEED;
    } else {
        barra->velocidadeX = 0.0;
    }

    barra->posicao.x += barra->velocidadeX * dt;

    if (barra->posicao.x < 0) {
        barra->posicao.x = 0;
    }
    if (barra->posicao.x + barra->largura > SCREEN_WIDTH) {
        barra->posicao.x = SCREEN_WIDTH - barra->largura;
    }
}

void desenharBarra(Barra *barra) {
    DrawRectangle((int)barra->posicao.x, (int)barra->posicao.y, 
                  (int)barra->largura, (int)barra->altura, BLACK);
    DrawRectangleLines((int)barra->posicao.x, (int)barra->posicao.y, 
                       (int)barra->largura, (int)barra->altura, BLACK);
}

void aumentarTamanhoBarra(Barra *barra, float tamanhoAdd) {
    barra->largura += tamanhoAdd;
    barra->largura = minimo(barra->largura, SCREEN_WIDTH * 0.5f);
}
void diminuirTamanhoBarra(Barra *barra, float tamanhoSub) {
    barra->largura -= tamanhoSub;
    barra->largura = maximo(barra->largura, 40.0f);
}
