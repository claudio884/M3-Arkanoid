#ifndef FASES_H
#define FASES_H

#include "tijolo.h"
#include "constantes.h"

struct Fase {
    Tijolo *tijolo;
    int qtdTijolos;
    int tijolosAtivos;
    int capacidadeMaxima;
    int *pontosBonus;
    float *multiplicadores;
};

void inicializarFase(Fase *fase, int numeroFase);

void desenharFase(Fase *fase);

bool verificarFaseCompleta(Fase *fase);

int contarTijolosAtivos(Fase *fase);

void liberarFase(Fase *fase);

int calcularBonusFase(Fase *fase, int indice);

#endif
