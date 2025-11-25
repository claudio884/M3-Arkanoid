#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../header/jogo.h"
#include "../header/cor.h"

static void gravarRanking(const char *arquivo, const Jogador *jogador) {
    FILE *f = fopen(arquivo, "a");
    if (!f) return;
    fprintf(f, "%s;%d;%d;%s\n", jogador->nome, jogador->pontos, jogador->tempoJogado, jogador->dataHora);
    fclose(f);
}

static void processarColisoesBolaTijolos(Jogo *jogo) {
    for (int i=0;i<jogo->fase.qtdTijolos;i++) {
        Tijolo *t = &jogo->fase.tijolos[i];
        if (!t->ativo) continue;
        colisaoTijolo(t, &jogo->bola);
        if (t->vida <= 0) {
            t->ativo = false;
            jogo->fase.tijolosAtivos--;
            int pontos = calcularBonusFase(&jogo->fase, i);
            modificaPontos(&jogo->jogador, pontos * (int)jogo->estado.multiplicadorPontos);
            criarExplosao(&jogo->particulas, t->x + t->largura/2, t->y + t->altura/2, obterCorTijolo(1), 20);
            if (rand() % 100 < 20 && jogo->qtdItens < MAX_ITENS) {
                gerarItem(jogo, (Posicao){ t->x + t->largura/2, t->y + t->altura/2 });
            }
        }
    }
}

void inicializarJogo(Jogo *jogo, const char *nomeJogador, int dificuldade) {
    inicializaBarra(&jogo->barra);
    inicializaBola(&jogo->bola, &jogo->barra);
    inicializaJogador(&jogo->jogador, nomeJogador);
    inicializarEstado(&jogo->estado);
    aplicarDificuldade(&jogo->estado, dificuldade);
    inicializarSistemaParticulas(&jogo->particulas);
    inicializarSom(&jogo->sons);

    jogo->qtdItens = 0;
    jogo->tempoInicio = 0;
    jogo->tempoDecorrido = 0;
    jogo->shakeX = 0;
    jogo->shakeY = 0;
    jogo->shakeIntensidade = 0;

    inicializarFase(&jogo->fase, 1);
}

void processarColisoes(Jogo *jogo) {
    processarColisoesBolaTijolos(jogo);
}

void gerarItem(Jogo *jogo, Posicao posicao) {
    if (jogo->qtdItens >= MAX_ITENS) return;
    int tipo = rand() % 6;
    inicializarItem(&jogo->itens[jogo->qtdItens], tipo, posicao.x - ITEM_LARGURA/2, posicao.y - ITEM_ALTURA/2);
    jogo->qtdItens++;
}

void aplicarEfeitoItem(Jogo *jogo, int tipoItem) {
    if (tipoItem == TIPO_ITEM_VIDA) {
        modificaVidas(&jogo->jogador, 1);
    } else if (tipoItem == TIPO_ITEM_AUMENTAR_BARRA) {
        modificarTamanhoBarra(&jogo->barra, TAMANHO_AUMENTO_BARRA);
    } else if (tipoItem == TIPO_ITEM_DIMINUIR_BARRA) {
        modificarTamanhoBarra(&jogo->barra, -TAMANHO_DIMINUIR_BARRA);
    } else if (tipoItem == TIPO_ITEM_PONTOS_EXTRA) {
        modificaPontos(&jogo->jogador, PONTOS_ITEM);
    } else if (tipoItem == TIPO_ITEM_MULTIPLICADOR) {
        jogo->estado.multiplicadorPontos = 2.0f;
        jogo->estado.tempoMultiplicador = 10 * 60;
    } else if (tipoItem == TIPO_ITEM_INVERSOR) {
        jogo->estado.inversorPontos = true;
        jogo->estado.tempoInversor = 10 * 60;
    }
    somItemColetado(&jogo->sons);
}

void atualizarJogo(Jogo *jogo, float dt) {
    atualizarMusicaFundo(&jogo->sons);

    if (jogo->estado.estadoAtual == ESTADO_PAUSA) return;

    atualizaBarra(&jogo->barra);
    atualizaBola(&jogo->bola, &jogo->barra, dt * jogo->estado.multiplicadorVelocidade);

    if (verificaColisaoBolaBarra(&jogo->bola, &jogo->barra)) somColisaoBarra(&jogo->sons);

    processarColisoes(jogo);

    for (int i=0;i<jogo->qtdItens;i++) {
        if (!jogo->itens[i].ativo) continue;
        atualizarPosicaoItem(&jogo->itens[i], dt);
        if (verificarColisaoItemComBarra(&jogo->itens[i], &jogo->barra)) {
            aplicarEfeitoItem(jogo, jogo->itens[i].tipo);
        }
    }

    atualizarParticulas(&jogo->particulas, dt);

    if (jogo->estado.tempoMultiplicador > 0) {
        jogo->estado.tempoMultiplicador--;
        if (jogo->estado.tempoMultiplicador == 0) jogo->estado.multiplicadorPontos = 1.0f;
    }
    if (jogo->estado.tempoInversor > 0) {
        jogo->estado.tempoInversor--;
        if (jogo->estado.tempoInversor == 0) jogo->estado.inversorPontos = false;
    }

    if (jogo->bola.presa) {
        if (jogo->jogador.vidas > 0) {
            modificaVidas(&jogo->jogador, -1);
            if (jogo->jogador.vidas > 0) resetaBola(&jogo->bola, &jogo->barra);
        }
    }

    if (verificarFaseCompleta(&jogo->fase)) {
        proximaFase(jogo);
    }

    jogo->tempoDecorrido += dt;
}

void desenharJogo(Jogo *jogo) {
    desenharFase(&jogo->fase);
    for (int i=0;i<jogo->qtdItens;i++) desenharItem(&jogo->itens[i]);
    desenhaBarra(&jogo->barra);
    desenhaBola(&jogo->bola);
    desenharParticulas(&jogo->particulas);
}

void proximaFase(Jogo *jogo) {
    liberarFase(&jogo->fase);
    inicializarFase(&jogo->fase, 1);
}

void reiniciarJogo(Jogo *jogo) {
    liberarFase(&jogo->fase);
    inicializarFase(&jogo->fase, 1);
    inicializaBarra(&jogo->barra);
    resetaBola(&jogo->bola, &jogo->barra);
    jogo->jogador.pontos = 0;
    jogo->jogador.vidas = VIDAS_INICIAIS;
}

void finalizarJogo(Jogo *jogo) {
    gravarRanking(ARQUIVO_RANKING, &jogo->jogador);
    descarregarSons(&jogo->sons);
    liberarFase(&jogo->fase);
}
