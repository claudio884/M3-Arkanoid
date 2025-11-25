#include <string.h>
#include "../header/menu.h"
#include "../header/estadoJogo.h"

void inicializarMenu(Menu *menu) {
    menu->opcao = 0;
    menu->totalOpcoes = 3;
    menu->tamanhoNome = 0;
    menu->nomeJogador[0] = '\0';
}

void desenharMenuPrincipal(Menu *menu) {
}

void desenharMenuDificuldade(Menu *menu) {
}

void desenharMenuRegistro(Menu *menu) {
}

void desenharMenuGameOver(Menu *menu, int pontuacao, int tempo) {
}

void desenharMenuVitoria(Menu *menu, int pontuacao, int tempo) {
}

void desenharMenuPausa(Menu *menu) {
}

int atualizarMenu(Menu *menu) {
    return 0;
}

bool atualizarMenuRegistro(Menu *menu) {
    return false;
}
