#ifndef BOLA_H
#define BOLA_H

#include "posicao.h"
#include "barra.h"

struct Bola {
    Posicao posicao;
    float raio;
    float velocidadeX;
    float velocidadeY;
    bool presa;
    Posicao rastro[10];
    int rastroBola;
};

void inicializaBola(Bola* bola, Barra* barra);
void atualizaBola(Bola* bola, Barra* barra, float deltaTime);
void desenhaBola(const Bola* bola);
bool verificaColisaoBolaBarra(const Bola* bola, const Barra* barra);
void lancaBola(Bola* bola, float velocidadeInicial);
void resetaBola(Bola* bola, Barra* barra);

#endif
