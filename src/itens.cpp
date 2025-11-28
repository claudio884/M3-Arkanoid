#include "../header/itens.h"
#include "../header/cores.h"
#include "../header/constantes.h"
#include "../header/estadoJogo.h"
#include "raylib.h"
#include <cmath>

void inicializarItem(Item *item, Posicao posicao, int tipo) {
    item->posicao = posicao;
    item->tipo = tipo;
    item->velocidadeY = ITEM_VELOCIDADE;
    item->largura = ITEM_LARGURA;
    item->altura = ITEM_ALTURA;
    item->ativo = true;
    item->animacao = 0.0f;
}

void atualizarItem(Item *item, float dt) {
    if (!item->ativo) return;
    
    item->posicao.y += item->velocidadeY * dt;
    item->animacao += dt * 5.0f;
    
    if (item->posicao.y > SCREEN_HEIGTH) {
        item->ativo = false;
    }
}
// TODO
void desenharItem(Item *item) {
    if (!item->ativo) return;
    
    float pulso = sinf(item->animacao) * 3.0f;
    float brilho = (sinf(item->animacao * 2.0f) + 1.0f) / 2.0f;
    
    Color cor = obterCorItem(item->tipo);
    
    DrawCircle((int)(item->posicao.x + item->largura / 2.0f), 
               (int)(item->posicao.y + item->altura / 2.0f), 
               item->largura / 2.0f + pulso + 5.0f, 
               Fade(cor, 0.3f * brilho));
    
    DrawRectangle((int)item->posicao.x, (int)item->posicao.y, 
                  (int)item->largura, (int)item->altura, cor);
    DrawRectangleLines((int)item->posicao.x, (int)item->posicao.y, 
                       (int)item->largura, (int)item->altura, BLACK);
    
    const char *texto = "";
    switch (item->tipo) {
        case TIPO_ITEM_VIDA:
            texto = "+V";
            break;
        case TIPO_ITEM_AUMENTAR_BARRA:
            texto = "+B";
            break;
        case TIPO_ITEM_DIMINUIR_BARRA:
            texto = "-B";
            break;
        case TIPO_ITEM_PONTOS_EXTRA:
            texto = "+P";
            break;
        case TIPO_ITEM_MULTIPLICADOR:
            texto = "x2";
            break;
        case TIPO_ITEM_INVERSOR:
            texto = "-P";
            break;
    }
    
    DrawText(texto, (int)item->posicao.x + 5, (int)item->posicao.y + 8, 14, BLACK);
}

bool verificarColisaoItem(Item *item, Barra *barra) {
    if (!item->ativo) return false;
    
    if (item->posicao.x + item->largura >= barra->posicao.x &&
        item->posicao.x <= barra->posicao.x + barra->largura &&
        item->posicao.y + item->altura >= barra->posicao.y &&
        item->posicao.y <= barra->posicao.y + barra->altura) {
        item->ativo = false;
        return true;
    }
    
    return false;
}
