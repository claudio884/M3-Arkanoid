#ifndef ITEM_H
#define ITEM_H

#include "posicao.h"
#include "barra.h"

struct Item {
    Posicao posicao;
    int tipo;
    float largura;
    float altura;
    bool ativo;
    float velocidadeY;
};

void inicializarItem(Item* item, int tipo, float x, float y);
void atualizarPosicaoItem(Item* item, float deltaTime);
void desenharItem(Item* item);
bool verificarColisaoItemComPaddle(Item* item, Barra* barra);

#endif