#include "../header/item.h"
#include "../header/constante.h"

void inicializarItem(Item* item, int tipo, float x, float y) {
    item->tipo = tipo;
    item->posicao.x = x;
    item->posicao.y = y;
    item->largura = ITEM_LARGURA;
    item->altura = ITEM_ALTURA;
    item->ativo = true;
    item->velocidadeY = ITEM_VELOCIDADE;
}

void atualizarPosicaoItem(Item* item, float deltaTime) {
    if (!item->ativo) return;
    item->posicao.y += item->velocidadeY * deltaTime;
    if (item->posicao.y > SCREEN_HEIGHT + item->altura) item->ativo = false;
}

bool verificarColisaoItemComBarra(Item* item, Barra* barra) {
    if (!item->ativo) return false;
    if (item->posicao.y + item->altura >= barra->posicao.y &&
        item->posicao.y <= barra->posicao.y + barra->altura &&
        item->posicao.x + item->largura >= barra->posicao.x &&
        item->posicao.x <= barra->posicao.x + barra->largura) {
        item->ativo = false;
        return true;
    }
    return false;
}

void desenharItem(Item* item) {
}
