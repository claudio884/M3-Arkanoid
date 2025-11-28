#include "../header/menu.h"
#include "../header/constantes.h"
#include "raylib.h"
#include <cstring>

void inicializarMenu(Menu *menu) {
    menu->opcaoSelecionada = 0;
    menu->totalOpcoes = 3;
    strcpy(menu->nomeJogador, "");
    menu->tamanhoNome = 0;
}

void desenharMenuPrincipal(Menu *menu) {
    ClearBackground(DARKGRAY);

    DrawText("ARKANOID", SCREEN_WIDTH / 2 - 150, 100, 60, BLACK);

    DrawText("ARKANOID", SCREEN_WIDTH / 2 - 150 + 3, 100 + 3, 60, RED);

    const char *opcoes[] = {"Iniciar Jogo", "Dificuldades", "Ranking"};

    for (int i = 0; i < 3; i++) {
        Color cor = (i == menu->opcaoSelecionada) ? (Color){255, 51, 51, 255} : WHITE;
        DrawText(opcoes[i], SCREEN_WIDTH / 2 - 100, 250 + i * 50, 30, cor);
    }

    DrawText("Use SETAS para navegar", SCREEN_WIDTH / 2 - 120, 450, 20, BLACK);
    DrawText("ENTER para selecionar", SCREEN_WIDTH / 2 - 110, 475, 20, BLACK);
    DrawText("ESC para sair", SCREEN_WIDTH / 2 - 70, 500, 20, BLACK);
}

void desenharMenuDificuldade(Menu *menu) {
    ClearBackground(DARKGRAY);

    DrawText("SELECIONE A DIFICULDADE", SCREEN_WIDTH / 2 - 275, 100, 40, BLACK);

    DrawText("SELECIONE A DIFICULDADE", SCREEN_WIDTH / 2 - 275 + 3, 100 + 3, 40, RED);

    const char *opcoes[] = {"Facil", "Medio (+0.25x velocidade)", "Dificil (+0.5x velocidade)"};

    for (int i = 0; i < 3; i++) {
        Color cor = (i == menu->opcaoSelecionada) ? (Color){255, 51, 51, 255} : BLACK;
        DrawText(opcoes[i], SCREEN_WIDTH / 2 - 150, 250 + i * 50, 25, cor);
    }

    DrawText("Use SETAS para navegar", SCREEN_WIDTH / 2 - 120, 450, 20, BLACK);
    DrawText("ENTER para selecionar", SCREEN_WIDTH / 2 - 110, 475, 20, BLACK);
    DrawText("ESC para voltar", SCREEN_WIDTH / 2 - 70, 500, 20, BLACK);
}

void desenharMenuGameOver(Menu *menu, int pontuacao, int tempo) {
    ClearBackground(DARKGRAY);

    DrawText("GAME OVER", SCREEN_WIDTH / 2 - 150, 100, 60, BLACK);
    DrawText("GAME OVER", SCREEN_WIDTH / 2 - 150 + 3, 100 + 3, 60, RED);

    DrawText(TextFormat("Pontuacao: %d", pontuacao), SCREEN_WIDTH / 2 - 100, 200, 30, BLACK);
    DrawText(TextFormat("Tempo: %d segundos", tempo), SCREEN_WIDTH / 2 - 120, 240, 30, BLACK);

    const char *opcoes[] = {"Jogar Novamente", "Menu Principal"};

    for (int i = 0; i < 2; i++) {
        Color cor = (i == menu->opcaoSelecionada) ? (Color){255, 51, 51, 255} : BLACK;
        DrawText(opcoes[i], SCREEN_WIDTH / 2 - 120, 320 + i * 50, 25, cor);
    }

    DrawText("Use SETAS para navegar", SCREEN_WIDTH / 2 - 120, 450, 20, BLACK);
    DrawText("ENTER para selecionar", SCREEN_WIDTH / 2 - 110, 475, 20, BLACK);
}

void desenharMenuVitoria(Menu *menu, int pontuacao, int tempo) {
    ClearBackground(DARKGRAY);

    DrawText("VITORIA!", SCREEN_WIDTH / 2 - 120, 100, 60, (Color){255, 200, 40, 255});
    DrawText("Parabens! Voce completou todas as fases!", SCREEN_WIDTH / 2 - 250, 180, 20, BLACK);
    DrawText("Parabens! Voce completou todas as fases!", SCREEN_WIDTH / 2 - 250 + 3, 180 + 3, 20, RED);

    DrawText(TextFormat("Pontuacao Final: %d", pontuacao), SCREEN_WIDTH / 2 - 120, 230, 30, BLACK);
    DrawText(TextFormat("Tempo Total: %d segundos", tempo), SCREEN_WIDTH / 2 - 140, 270, 30, BLACK);

    const char *opcoes[] = {"Jogar Novamente", "Menu Principal"};

    for (int i = 0; i < 2; i++) {
        Color cor = (i == menu->opcaoSelecionada) ? (Color){255, 51, 51, 255} : BLACK;
        DrawText(opcoes[i], SCREEN_WIDTH / 2 - 120, 340 + i * 50, 25, cor);
    }

    DrawText("Use SETAS para navegar", SCREEN_WIDTH / 2 - 120, 450, 20, BLACK);
    DrawText("ENTER para selecionar", SCREEN_WIDTH / 2 - 110, 475, 20, BLACK);
}

void desenharMenuPausa(Menu *menu) {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGTH, Fade(BLACK, 0.7f));

    DrawText("PAUSADO", SCREEN_WIDTH / 2 - 100, 150, 50, WHITE);

    const char *opcoes[] = {"Continuar", "Menu Principal"};

    for (int i = 0; i < 2; i++) {
        Color cor = (i == menu->opcaoSelecionada) ? (Color){255, 51, 51, 255} : WHITE;
        DrawText(opcoes[i], SCREEN_WIDTH / 2 - 80, 280 + i * 50, 25, cor);
    }

    DrawText("Use SETAS para navegar", SCREEN_WIDTH / 2 - 120, 400, 20, BLACK);
    DrawText("ENTER para selecionar", SCREEN_WIDTH / 2 - 110, 425, 20, BLACK);
}

int atualizarMenu(Menu *menu) {
    if (IsKeyPressed(KEY_UP)) {
        menu->opcaoSelecionada--;
        if (menu->opcaoSelecionada < 0) {
            menu->opcaoSelecionada = menu->totalOpcoes - 1;
        }
    }

    if (IsKeyPressed(KEY_DOWN)) {
        menu->opcaoSelecionada++;
        if (menu->opcaoSelecionada >= menu->totalOpcoes) {
            menu->opcaoSelecionada = 0;
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        return menu->opcaoSelecionada;
    }

    return -1;
}

void desenharMenuRegistro(Menu *menu) {
    ClearBackground(DARKGRAY);

    int tituloLargura = MeasureText("DIGITE SEU NOME", 40);
    DrawText("DIGITE SEU NOME", SCREEN_WIDTH / 2 - tituloLargura / 2, 100, 40, BLACK);
    DrawText("DIGITE SEU NOME", SCREEN_WIDTH / 2 - tituloLargura / 2 + 3, 100 + 3, 40, RED);

    DrawRectangle(SCREEN_WIDTH / 2 - 200, 200, 400, 60, (Color){153, 153, 153, 255});
    DrawRectangleLines(SCREEN_WIDTH / 2 - 200, 200, 400, 60, WHITE);

    if (menu->tamanhoNome > 0) {
        int textoLargura = MeasureText(menu->nomeJogador, 30);
        DrawText(menu->nomeJogador, SCREEN_WIDTH / 2 - textoLargura / 2, 215, 30, BLACK);
    } else {
        int placeholderLargura = MeasureText("Digite aqui...", 30);
        DrawText("Digite aqui...", SCREEN_WIDTH / 2 - placeholderLargura / 2, 215, 30, BLACK);
    }

    DrawText("Digite seu nome (max 20 caracteres)", 
             SCREEN_WIDTH / 2 - 180, 280, 20, BLACK);
    DrawText("ENTER para confirmar", 
             SCREEN_WIDTH / 2 - 120, 320, 20, BLACK);
    DrawText("BACKSPACE para apagar", 
             SCREEN_WIDTH / 2 - 135, 345, 20, BLACK);
    DrawText("ESC para voltar", 
             SCREEN_WIDTH / 2 - 75, 370, 20, BLACK);
}

bool atualizarMenuRegistro(Menu *menu) {
    int tecla = GetCharPressed();

    while (tecla > 0) {
        if ((tecla >= 32) && (tecla <= 125) && (menu->tamanhoNome < 20)) {
            menu->nomeJogador[menu->tamanhoNome] = (char)tecla;
            menu->nomeJogador[menu->tamanhoNome + 1] = '\0';
            menu->tamanhoNome++;
        }
        tecla = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (menu->tamanhoNome > 0) {
            menu->tamanhoNome--;
            menu->nomeJogador[menu->tamanhoNome] = '\0';
        }
    }

    if (IsKeyPressed(KEY_ENTER) && menu->tamanhoNome > 0) {
        return true;
    }

    return false;
}
