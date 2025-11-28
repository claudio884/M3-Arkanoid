#ifndef BOLA_H
#define BOLA_H

#include "barra.h"

struct Bola {
    Posicao posicao;
    float raio;
    float velocidadeX;
    float velocidadeY;
    bool presa;
    Posicao rastro[10];
    int rastroIndex;
};

void inicializarBola(Bola *bola, Barra *barra); 

void atualizarBola(Bola *bola, Barra *barra, float dt);

void desenharBola(Bola *bola);

void lancarBola(Bola *bola, float velocidadeBase);

bool verificarColisaoBarra(Bola *bola, Barra *barra);

void resetarBola(Bola *bola, Barra *barra);

#endif
