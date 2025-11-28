#include "../header/jogo.h"
#include "../header/sons.h" 
#include "../header/utils.h"
#include "../header/graficos.h"
#include "../header/cores.h"
#include "raylib.h"
#include <cstring>

void inicializarJogo(Jogo *jogo, const char *nomeJogador, int dificuldade) {
    inicializarEstado(&jogo->estado);
    aplicarDificuldade(&jogo->estado, dificuldade);
    jogo->estado.faseAtual = 1;
    
    inicializarJogador(&jogo->jogador, nomeJogador);
    inicializarBarra(&jogo->barra);
    inicializarBola(&jogo->bola, &jogo->barra);
    inicializarFase(&jogo->fase, jogo->estado.faseAtual);
    inicializarSistemaParticulas(&jogo->particulas);
    
    jogo->qtdItens = 0;
    for (int i = 0; i < MAX_ITENS; i++) {
        jogo->itens[i].ativo = false;
    }
    
    inicializarSons(&jogo->sons);
    tocarMusicaFundo(&jogo->sons);
    
    jogo->tempoInicio = GetTime();
    jogo->tempoDecorrido = 0.0f;
    jogo->shakeX = 0.0f;
    jogo->shakeY = 0.0f;
    jogo->shakeIntensidade = 0.0f;
}

void atualizarJogo(Jogo *jogo, float dt) {
    atualizarMusicaFundo(&jogo->sons);
    atualizarParticulas(&jogo->particulas, dt);
    
    if (jogo->shakeIntensidade > 0.0f) {
        jogo->shakeIntensidade -= dt * 5.0f;
        if (jogo->shakeIntensidade < 0.0f) jogo->shakeIntensidade = 0.0f;
        jogo->shakeX = (GetRandomValue(-100, 100) / 100.0f) * jogo->shakeIntensidade * 10.0f;
        jogo->shakeY = (GetRandomValue(-100, 100) / 100.0f) * jogo->shakeIntensidade * 10.0f;
    } else {
        jogo->shakeX = 0.0f;
        jogo->shakeY = 0.0f;
    }
    
    jogo->tempoDecorrido = GetTime() - jogo->tempoInicio;
    atualizarTempo(&jogo->jogador, (int)jogo->tempoDecorrido);
    
    if (IsKeyPressed(KEY_SPACE)) {
        lancarBola(&jogo->bola, BOLA_VELOCIDADE_BASE * jogo->estado.multiplicadorVelocidade);
    }
    
    atualizarBarra(&jogo->barra, dt);
    atualizarBola(&jogo->bola, &jogo->barra, dt);
    
    for (int i = 0; i < jogo->qtdItens; i++) {
        if (jogo->itens[i].ativo) {
            atualizarItem(&jogo->itens[i], dt);
        }
    }
    
    processarColisoes(jogo);
    
    if (jogo->estado.tempoMultiplicador > 0) {
        jogo->estado.tempoMultiplicador--;
        if (jogo->estado.tempoMultiplicador <= 0) {
            jogo->estado.multiplicadorPontos = 1.0f;
        }
    }
    
    if (jogo->estado.tempoInversor > 0) {
        jogo->estado.tempoInversor--;
        if (jogo->estado.tempoInversor <= 0) {
            jogo->estado.inversorPontos = false;
        }
    }
    
    if (jogo->bola.posicao.y - jogo->bola.raio > SCREEN_HEIGTH) {
        removerVida(&jogo->jogador);
        tocarSomPerdeuVida(&jogo->sons);
        
        if (jogo->jogador.vidas <= 0) {
            mudarEstado(&jogo->estado, ESTADO_GAME_OVER);
        } else {
            resetarBola(&jogo->bola, &jogo->barra);
        }
    }
    
    if (verificarFaseCompleta(&jogo->fase)) {
        tocarSomFaseCompleta(&jogo->sons);
        proximaFase(jogo);
    }
}

void desenharJogo(Jogo *jogo) {
    desenharFundo(jogo->estado.faseAtual, (float)GetTime());
    
    desenharFase(&jogo->fase);
    desenharParticulas(&jogo->particulas);
    desenharBarra(&jogo->barra);
    desenharBola(&jogo->bola);
    
    for (int i = 0; i < jogo->qtdItens; i++) {
        if (jogo->itens[i].ativo) {
            desenharItem(&jogo->itens[i]);
        }
    }
    
    DrawText(TextFormat("Pontos: %d", jogo->jogador.pontuacao), 10, 10, 20, WHITE);
    DrawText(TextFormat("Vidas: %d", jogo->jogador.vidas), 10, 35, 20, WHITE);
    DrawText(TextFormat("Tempo: %d s", jogo->jogador.tempoJogado), 10, 60, 20, WHITE);
    DrawText(TextFormat("Fase: %d", jogo->estado.faseAtual), SCREEN_WIDTH - 100, 10, 20, WHITE);
    int tijolosAtivos = contarTijolosRecursivo(jogo->fase.tijolo, 0, jogo->fase.qtdTijolos - 1);
    DrawText(TextFormat("tijolos: %d", tijolosAtivos), SCREEN_WIDTH - 100, 35, 20, WHITE);

    if (jogo->estado.multiplicadorPontos > 1.0f) {
        DrawText("MULTIPLICADOR x2!", SCREEN_WIDTH / 2 - 100, 10, 20, GOLD);
    }
    
    if (jogo->estado.inversorPontos) {
        DrawText("INVERSOR ATIVO!", SCREEN_WIDTH / 2 - 90, 35, 20, RED);
    }
    
    if (jogo->bola.presa) {
        DrawText("Pressione ESPACO para lancar", SCREEN_WIDTH / 2 - 150, 
                 SCREEN_HEIGTH / 2, 20, DARKGRAY);
    }
}

void processarColisoes(Jogo *jogo) {
    if (verificarColisaoBarra(&jogo->bola, &jogo->barra)) {
        tocarSomColisaoBarra(&jogo->sons);
    }
    
    for (int i = 0; i < jogo->fase.qtdTijolos; i++) {
        if (jogo->fase.tijolo[i].ativo) {
            if (verificarColisaoTijolo(&jogo->bola, &jogo->fase.tijolo[i])) {
                tocarSomColisaoTijolo(&jogo->sons);
                
                int pontosTijolo = PONTOS_TIJOLO_VIDA1;
                if (jogo->fase.tijolo[i].vida == 3) {
                    pontosTijolo = PONTOS_TIJOLO_VIDA3;
                } else if (jogo->fase.tijolo[i].vida == 2) {
                    pontosTijolo = PONTOS_TIJOLO_VIDA2;
                }
                
                pontosTijolo = (int)(pontosTijolo * jogo->estado.multiplicadorPontos);
                
                if (jogo->estado.inversorPontos) {
                    pontosTijolo = -pontosTijolo;
                }
                
                atualizarPontuacao(&jogo->jogador, pontosTijolo);
                
                Color corTijolo = obterCorTijolo(jogo->fase.tijolo[i].vida);
                
                danificarTijolo(&jogo->fase.tijolo[i]);
                
                if (!jogo->fase.tijolo[i].ativo) {
                    float centroX = jogo->fase.tijolo[i].posicao.x + jogo->fase.tijolo[i].largura / 2.0f;
                    float centroY = jogo->fase.tijolo[i].posicao.y + jogo->fase.tijolo[i].altura / 2.0f;
                    criarExplosao(&jogo->particulas, centroX, centroY, corTijolo, 15);
                    jogo->shakeIntensidade = 0.5f;
                    
                    if (GetRandomValue(0, 100) < 30) {
                        Posicao pos;
                        pos.x = jogo->fase.tijolo[i].posicao.x + jogo->fase.tijolo[i].largura / 2.0f - ITEM_LARGURA / 2.0f;
                        pos.y = jogo->fase.tijolo[i].posicao.y;
                        gerarItem(jogo, pos);
                    }
                } else {
                    float centroX = jogo->fase.tijolo[i].posicao.x + jogo->fase.tijolo[i].largura / 2.0f;
                    float centroY = jogo->fase.tijolo[i].posicao.y + jogo->fase.tijolo[i].altura / 2.0f;
                    criarExplosao(&jogo->particulas, centroX, centroY, corTijolo, 5);
                }
                
                break;
            }
        }
    }
    
    for (int i = 0; i < jogo->qtdItens; i++) {
        if (jogo->itens[i].ativo) {
            if (verificarColisaoItem(&jogo->itens[i], &jogo->barra)) {
                tocarSomItemColetado(&jogo->sons);
                aplicarEfeitoItem(jogo, jogo->itens[i].tipo);
            }
        }
    }
}

void gerarItem(Jogo *jogo, Posicao posicao) {
    if (jogo->qtdItens >= MAX_ITENS) return;
    
    int tipo = GetRandomValue(0, 5);
    
    inicializarItem(&jogo->itens[jogo->qtdItens], posicao, tipo);
    jogo->qtdItens++;
}

void aplicarEfeitoItem(Jogo *jogo, int tipoItem) {
    switch (tipoItem) {
        case TIPO_ITEM_VIDA:
            adicionarVida(&jogo->jogador);
            break;
        case TIPO_ITEM_AUMENTAR_BARRA:
            aumentarTamanhoBarra(&jogo->barra, TAMANHO_AUMENTO_BARRA);
            break;
        case TIPO_ITEM_DIMINUIR_BARRA:
            diminuirTamanhoBarra(&jogo->barra, TAMANHO_DIMINUIR_BARRA);
            break;
        case TIPO_ITEM_PONTOS_EXTRA:
            atualizarPontuacao(&jogo->jogador, PONTOS_ITEM);
            break;
        case TIPO_ITEM_MULTIPLICADOR:
            jogo->estado.multiplicadorPontos = 2.0f;
            jogo->estado.tempoMultiplicador = 600;
            break;
        case TIPO_ITEM_INVERSOR:
            jogo->estado.inversorPontos = true;
            jogo->estado.tempoInversor = 300;
            break;
    }
}

void proximaFase(Jogo *jogo) {
    int bonusFase = calcularPontosRecursivo(jogo->estado.faseAtual, 50);
    atualizarPontuacao(&jogo->jogador, bonusFase);
    
    liberarFase(&jogo->fase);
    
    jogo->estado.faseAtual++;
    
    if (jogo->estado.faseAtual > MAX_FASES) {
        int bonusVitoria = somarRecursivo(jogo->jogador.vidas) * 100;
        atualizarPontuacao(&jogo->jogador, bonusVitoria);
        mudarEstado(&jogo->estado, ESTADO_VITORIA);
        return;
    }
    
    inicializarFase(&jogo->fase, jogo->estado.faseAtual);
    resetarBola(&jogo->bola, &jogo->barra);
    
    jogo->qtdItens = 0;
    for (int i = 0; i < MAX_ITENS; i++) {
        jogo->itens[i].ativo = false;
    }
}

void reiniciarJogo(Jogo *jogo) {
    char nomeTemp[50];
    strncpy(nomeTemp, jogo->jogador.nome, 49);
    int dificuldadeTemp = jogo->estado.dificuldade;
    
    liberarFase(&jogo->fase);
    descarregarSons(&jogo->sons);
    inicializarJogo(jogo, nomeTemp, dificuldadeTemp);
}

void finalizarJogo(Jogo *jogo) {
    liberarFase(&jogo->fase);
    pararMusicaFundo(&jogo->sons);
    descarregarSons(&jogo->sons);
}
