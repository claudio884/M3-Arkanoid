#include "raylib.h"
#include "header/jogo.h"
#include "header/menu.h"
#include "header/ranking.h"
#include "header/estadoJogo.h"
#include "header/constantes.h"
#include <cstring> 

int FASE_ATUAL = 1;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGTH, "Arkanoid - Trabalho M3");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    
    Menu menu;
    Ranking ranking;
    Jogo jogo;
    EstadoJogo estadoGlobal;
    
    inicializarMenu(&menu);
    inicializarRanking(&ranking);
    carregarRanking(&ranking, ARQUIVO_RANKING);
    inicializarEstado(&estadoGlobal);
    
    char nomeJogador[50] = "Jogador";
    int dificuldadeSelecionada = DIFICULDADE_FACIL;
    bool jogoInicializado = false;
    
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        BeginDrawing();
        
        if (estadoGlobal.estadoAtual == ESTADO_MENU) {
            menu.totalOpcoes = 3;
            desenharMenuPrincipal(&menu);
            
            int opcao = atualizarMenu(&menu);
            if (opcao == 0) {
                mudarEstado(&estadoGlobal, ESTADO_REGISTRO);
            } else if (opcao == 1) {
                menu.opcaoSelecionada = 0;
                mudarEstado(&estadoGlobal, ESTADO_DIFICULDADE);
            } else if (opcao == 2) {
                mudarEstado(&estadoGlobal, ESTADO_RANKING);
            }
        }
        else if (estadoGlobal.estadoAtual == ESTADO_DIFICULDADE) {
            menu.totalOpcoes = 3;
            desenharMenuDificuldade(&menu);
            
            int opcao = atualizarMenu(&menu);
            if (opcao >= 0 && opcao <= 2) {
                dificuldadeSelecionada = opcao;
                menu.opcaoSelecionada = 0;
                mudarEstado(&estadoGlobal, ESTADO_MENU);
            }
            
            if (IsKeyPressed(KEY_ESCAPE)) {
                menu.opcaoSelecionada = 0;
                mudarEstado(&estadoGlobal, ESTADO_MENU);
            }
        }
        else if (estadoGlobal.estadoAtual == ESTADO_RANKING) {
            desenharRanking(&ranking);
            
            if (IsKeyPressed(KEY_ESCAPE)) {
                mudarEstado(&estadoGlobal, ESTADO_MENU);
            }
        }
        else if (estadoGlobal.estadoAtual == ESTADO_JOGO) {
            if (IsKeyPressed(KEY_ESCAPE)) {
                menu.opcaoSelecionada = 0;
                menu.totalOpcoes = 2;
                mudarEstado(&estadoGlobal, ESTADO_PAUSA);
            }
            
            atualizarJogo(&jogo, dt);
            desenharJogo(&jogo);
            
            if (jogo.estado.estadoAtual == ESTADO_GAME_OVER) {
                adicionarJogadorRanking(&ranking, jogo.jogador);
                salvarRanking(&ranking, ARQUIVO_RANKING);
                menu.opcaoSelecionada = 0;
                menu.totalOpcoes = 2;
                mudarEstado(&estadoGlobal, ESTADO_GAME_OVER);
            } else if (jogo.estado.estadoAtual == ESTADO_VITORIA) {
                adicionarJogadorRanking(&ranking, jogo.jogador);
                salvarRanking(&ranking, ARQUIVO_RANKING);
                menu.opcaoSelecionada = 0;
                menu.totalOpcoes = 2;
                mudarEstado(&estadoGlobal, ESTADO_VITORIA);
            }
        }
        else if (estadoGlobal.estadoAtual == ESTADO_PAUSA) {
            desenharJogo(&jogo);
            menu.totalOpcoes = 2;
            desenharMenuPausa(&menu);
            
            int opcao = atualizarMenu(&menu);
            if (opcao == 0) {
                mudarEstado(&estadoGlobal, ESTADO_JOGO);
            } else if (opcao == 1) {
                finalizarJogo(&jogo);
                jogoInicializado = false;
                menu.opcaoSelecionada = 0;
                mudarEstado(&estadoGlobal, ESTADO_MENU);
            }
            
            if (IsKeyPressed(KEY_ESCAPE)) {
                mudarEstado(&estadoGlobal, ESTADO_JOGO);
            }
        }
        else if (estadoGlobal.estadoAtual == ESTADO_GAME_OVER) {
            menu.totalOpcoes = 2;
            desenharMenuGameOver(&menu, jogo.jogador.pontuacao, jogo.jogador.tempoJogado);
            
            int opcao = atualizarMenu(&menu);
            if (opcao == 0) {
                reiniciarJogo(&jogo);
                mudarEstado(&estadoGlobal, ESTADO_JOGO);
            } else if (opcao == 1) {
                finalizarJogo(&jogo);
                jogoInicializado = false;
                menu.opcaoSelecionada = 0;
                mudarEstado(&estadoGlobal, ESTADO_MENU);
            }
        }
        else if (estadoGlobal.estadoAtual == ESTADO_VITORIA) {
            menu.totalOpcoes = 2;
            desenharMenuVitoria(&menu, jogo.jogador.pontuacao, jogo.jogador.tempoJogado);
            
            int opcao = atualizarMenu(&menu);
            if (opcao == 0) {
                reiniciarJogo(&jogo);
                mudarEstado(&estadoGlobal, ESTADO_JOGO);
            } else if (opcao == 1) {
                finalizarJogo(&jogo);
                jogoInicializado = false;
                menu.opcaoSelecionada = 0;
                mudarEstado(&estadoGlobal, ESTADO_MENU);
            }
        }
        else if (estadoGlobal.estadoAtual == ESTADO_REGISTRO) {
            desenharMenuRegistro(&menu);
            
            if (atualizarMenuRegistro(&menu)) {
                strncpy(nomeJogador, menu.nomeJogador, 49);
                nomeJogador[49] = '\0';
                
                if (!jogoInicializado) {
                    inicializarJogo(&jogo, nomeJogador, dificuldadeSelecionada);
                    jogoInicializado = true;
                }
                mudarEstado(&estadoGlobal, ESTADO_JOGO);
                mudarEstado(&jogo.estado, ESTADO_JOGO);
            }
            
            if (IsKeyPressed(KEY_ESCAPE)) {
                menu.opcaoSelecionada = 0;
                mudarEstado(&estadoGlobal, ESTADO_MENU);
            }
        }
        
        EndDrawing();
    }
    
    if (jogoInicializado) {
        finalizarJogo(&jogo);
    }
    
    CloseWindow();
    
    return 0;
}
