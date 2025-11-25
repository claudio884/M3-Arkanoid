#include "../header/tijolo.h"
#include "../header/cor.h"
#include "../header/constante.h"

void inicializaTijolo(Tijolo* tijolo, float x, float y, int vidaAtual) {
    tijolo->x = x;
    tijolo->y = y;
    tijolo->largura = TIJOLO_LARGURA;
    tijolo->altura = TIJOLO_ALTURA;
    tijolo->vida = vidaAtual;
    tijolo->ativo = true;
}

void desenharTijolo(const Tijolo *tijolo) {
    if (!tijolo || !tijolo->ativo) return;
    Color cor = obterCorTijolo(tijolo->vida);
}

void destroiTijolo(Tijolo* tijolo) {
    if (!tijolo) return;
    tijolo->ativo = false;
    tijolo->vida = 0;
}

void colisaoTijolo(Tijolo* tijolo, Bola* bola) {
    if (!tijolo || !bola || !tijolo->ativo) return;
    if (bola->posicao.y + bola->raio >= tijolo->y &&
        bola->posicao.y - bola->raio <= tijolo->y + tijolo->altura &&
        bola->posicao.x + bola->raio >= tijolo->x &&
        bola->posicao.x - bola->raio <= tijolo->x + tijolo->largura) {
        
        if (fabsf((bola->posicao.y - (tijolo->y + tijolo->altura/2))) > 
            fabsf((bola->posicao.x - (tijolo->x + tijolo->largura/2)))) {
            bola->velocidadeY *= -1;
        } else {
            bola->velocidadeX *= -1;
        }
        tijolo->vida -= 1;
    }
}
