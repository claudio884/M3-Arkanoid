#ifndef BARRA_H
#define BARRA_H
#include "posicao.h"

struct Barra {
    Posicao posicao;
    float largura;
    float altura;
    float velocidadeX;
};

void inicializaBarra(Barra* barraX);
void atualizaBarra(Barra* barraX);
void desenhaBarra(const Barra* barraX);
void modificarTamanhoBarra(Barra* barraX, float tamanhoDelta);

#endif
