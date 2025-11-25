#include "../header/jogo.h"
#include "../header/menu.h"

int main() {
    Menu menu;
    inicializarMenu(&menu);

    int estado = 0;
    int dificuldadeSelecionada = DIFICULDADE_MEDIO;

    while (true) {
        if (estado == 0) {
            menu.totalOpcoes = 3;
            desenharMenuPrincipal(&menu);
            if (atualizarMenu(&menu)) {
                if (menu.opcao == 0) { estado = 1; menu.opcao = 0; }
                else if (menu.opcao == 1) { }
                else { return 0; }
            }
        } else if (estado == 1) {
            menu.totalOpcoes = 3;
            desenharMenuDificuldade(&menu);
            if (atualizarMenu(&menu)) {
                dificuldadeSelecionada = menu.opcao;
                estado = 2;
            }
        } else if (estado == 2) {
            desenharMenuRegistro(&menu);
            if (atualizarMenuRegistro(&menu)) {
                Jogo jogo;
                inicializarJogo(&jogo, menu.nomeJogador, dificuldadeSelecionada);
                
                while (true) {
                    float dt = 0.016f;
                    atualizarJogo(&jogo, dt);
                    desenharJogo(&jogo);
                    
                    if (jogo.jogador.vidas <= 0) {
                        finalizarJogo(&jogo);
                        estado = 0;
                        break;
                    }
                }
            }
        }
    }

    return 0;
}
