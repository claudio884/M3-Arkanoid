#include "../header/fases.h"
#include "../header/constantes.h"
#include "../header/utils.h"
#include "raylib.h"
#include <cstdlib>

void inicializarFase(Fase *fase, int numeroFase) {
    fase->qtdTijolos = 0;
    fase->tijolosAtivos = 0;
    
    int linhas = 3 + numeroFase;
    int colunas = 10;
    fase->capacidadeMaxima = linhas * colunas;

    fase->tijolo = (Tijolo*)malloc(fase->capacidadeMaxima * sizeof(Tijolo));
    fase->pontosBonus = alocarArrayInt(fase->capacidadeMaxima);
    fase->multiplicadores = alocarArrayFloat(fase->capacidadeMaxima);
    float espacamentoX = 0.0f;
    float espacamentoY = 0.0f;
    float inicioX = (SCREEN_WIDTH - (colunas * TIJOLO_LARGURA + (colunas - 1) * espacamentoX)) / 2.0f;
    float inicioY = 120.0f;

    for (int i = 0; i < linhas && fase->qtdTijolos < fase->capacidadeMaxima; i++) {
        for (int j = 0; j < colunas && fase->qtdTijolos < fase->capacidadeMaxima; j++) {
            float x = inicioX + j * (TIJOLO_LARGURA + espacamentoX);
            float y = inicioY + i * (TIJOLO_ALTURA + espacamentoY);
            
            int vida = 1;
            int aleatorio = GetRandomValue(0, 100);
            
            if (numeroFase >= 2) {
                if (aleatorio < 20) {
                    vida = 3;
                } else if (aleatorio < 50) {
                    vida = 2;
                } else {
                    vida = 1;
                }
            } else {
                if (aleatorio < 30) {
                    vida = 2;
                } else {
                    vida = 1;
                }
            }

            inicializarTijolo(&fase->tijolo[fase->qtdTijolos], x, y, vida);
            fase->qtdTijolos++;
            fase->tijolosAtivos++;
        }
    }
}

void desenharFase(Fase *fase) {
    for (int i = 0; i < fase->qtdTijolos; i++) {
        desenharTijolo(&fase->tijolo[i]);
    }
}

bool verificarFaseCompleta(Fase *fase) {
    return contarTijolosAtivos(fase) == 0;
}

int contarTijolosAtivos(Fase *fase) {
    if (fase->qtdTijolos == 0) {
        fase->tijolosAtivos = 0;
        return 0;
    }
    int count = contarTijolosRecursivo(fase->tijolo, 0, fase->qtdTijolos - 1);
    fase->tijolosAtivos = count;
    return count;
}

void liberarFase(Fase *fase) {
    if (fase->tijolo != NULL) {
        free(fase->tijolo);
        fase->tijolo = NULL;
    }
    if (fase->pontosBonus != NULL) {
        liberarArray(fase->pontosBonus);
        fase->pontosBonus = NULL;
    }
    if (fase->multiplicadores != NULL) {
        liberarArray(fase->multiplicadores);
        fase->multiplicadores = NULL;
    }
}

int calcularBonusFase(Fase *fase, int indice) {
    if (indice < 0 || indice >= fase->qtdTijolos) {
        return 0;
    }
    return fase->pontosBonus[indice];
}
