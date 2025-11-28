#ifndef ITENS_H
#define ITENS_H

#include "barra.h"

struct Item {
     Posicao posicao;
     int tipo; 
     float velocidadeY;
     float largura;
     float altura;
     bool ativo;
     float animacao;
};  

void inicializarItem(Item *item, Posicao posicao, int tipo);

void atualizarItem(Item *item, float dt);

void desenharItem(Item *item);

bool verificarColisaoItem(Item *item, Barra *barra);

#endif
