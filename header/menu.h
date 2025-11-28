#ifndef MENU_H
#define MENU_H

struct Menu {
    int opcaoSelecionada;
    int totalOpcoes;
    char nomeJogador[50];
    int tamanhoNome;
};

void inicializarMenu(Menu *menu);

void desenharMenuPrincipal(Menu *menu);

void desenharMenuDificuldade(Menu *menu);

void desenharMenuRegistro(Menu *menu);

void desenharMenuGameOver(Menu *menu, int pontuacao, int tempo);

void desenharMenuVitoria(Menu *menu, int pontuacao, int tempo);

void desenharMenuPausa(Menu *menu);

int atualizarMenu(Menu *menu);

bool atualizarMenuRegistro(Menu *menu);

#endif
