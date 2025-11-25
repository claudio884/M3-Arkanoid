#ifndef SONS_H
#define SONS_H

#include "raylib.h"

struct Sons {
    Sound colisaoBarra;
    Sound colisaoBloco;
    Sound itemColetado;
    Sound perdeuVida;
    Sound faseCompleta;
    Music musicaFundo;
};

void inicializarSons(Sons *sons);

void descarregarSons(Sons *sons);

void tocarSomColisaoBarra(Sons *sons);

void tocarSomColisaoBloco(Sons *sons);

void tocarSomItemColetado(Sons *sons);

void tocarSomPerdeuVida(Sons *sons);

void tocarSomFaseCompleta(Sons *sons);

void tocarMusicaFundo(Sons *sons);

void pararMusicaFundo(Sons *sons);

void atualizarMusicaFundo(Sons *sons);

#endif