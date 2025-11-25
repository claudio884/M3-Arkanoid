#include <stdlib.h>
#include "../header/fase.h"
#include "../header/cor.h"

void inicializarFase(Fase *fase, int numeroFase) {
    fase->capacidadeMaxima = MAX_TIJOLOS;
    fase->tijolos = (Tijolo*) malloc(sizeof(Tijolo) * fase->capacidadeMaxima);
    fase->qtdTijolos = 0;
    fase->tijolosAtivos = 0;
    fase->pontosBonus = (int*) malloc(sizeof(int) * fase->capacidadeMaxima);
    fase->multiplicadores = (float*) malloc(sizeof(float) * fase->capacidadeMaxima);

    int colunas = 10;
    int linhas = 5 + numeroFase; if (linhas > 8) linhas = 8;
    float inicioX = (SCREEN_WIDTH - colunas * TIJOLO_LARGURA) / 2.0f;
    float inicioY = 80.0f;

    for (int l=0; l<linhas; l++) {
        for (int c=0; c<colunas; c++) {
            if (fase->qtdTijolos >= fase->capacidadeMaxima) break;
            Tijolo *t = &fase->tijolos[fase->qtdTijolos++];
            inicializaTijolo(t, inicioX + c * TIJOLO_LARGURA, inicioY + l * TIJOLO_ALTURA, 1 + (l % 3));
            fase->pontosBonus[fase->qtdTijolos-1] = 0;
            fase->multiplicadores[fase->qtdTijolos-1] = 1.0f;
        }
    }
    fase->tijolosAtivos = fase->qtdTijolos;
}

void desenharFase(Fase *fase) {
    for (int i=0; i<fase->qtdTijolos; i++) {
        if (!fase->tijolos[i].ativo) continue;
        desenharTijolo(&fase->tijolos[i]);
    }
}

bool verificarFaseCompleta(Fase *fase) {
    return fase->tijolosAtivos <= 0;
}

int contarTijolosAtivos(Fase *fase) {
    int ativos = 0;
    for (int i=0;i<fase->qtdTijolos;i++) if (fase->tijolos[i].ativo) ativos++;
    return ativos;
}

int calcularBonusFase(Fase *fase, int indice) {
    if (indice < 0 || indice >= fase->qtdTijolos) return 0;
    int vida = fase->tijolos[indice].vida;
    if (vida == 1) return PONTOS_TIJOLO_VIDA1;
    if (vida == 2) return PONTOS_TIJOLO_VIDA2;
    return PONTOS_TIJOLO_VIDA3;
}

void liberarFase(Fase *fase) {
    if (fase->tijolos) free(fase->tijolos);
    if (fase->pontosBonus) free(fase->pontosBonus);
    if (fase->multiplicadores) free(fase->multiplicadores);
    fase->tijolos = NULL;
    fase->pontosBonus = NULL;
    fase->multiplicadores = NULL;
    fase->qtdTijolos = 0;
    fase->tijolosAtivos = 0;
}
