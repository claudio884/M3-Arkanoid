#include "../header/ranking.h"
#include "../header/constantes.h"
#include "raylib.h"
#include <cstring>
#include <fstream>

using namespace std;

void inicializarRanking(Ranking *ranking) {
    ranking->qtdJogadores = 0;
    for (int i = 0; i < MAX_JOGADORES; i++) {
        ranking->jogadores[i].pontuacao = 0;
        ranking->jogadores[i].tempoJogado = 0;
        ranking->jogadores[i].vidas = 0;
        strcpy(ranking->jogadores[i].nome, "");
        strcpy(ranking->jogadores[i].data, "");
    }
}

void adicionarJogadorRanking(Ranking *ranking, Jogador jogador) {
    if (ranking->qtdJogadores < MAX_JOGADORES) {
        ranking->jogadores[ranking->qtdJogadores] = jogador;
        ranking->qtdJogadores++;
    } else {
        int menorIndice = 0;
        int menorPontuacao = ranking->jogadores[0].pontuacao;

        for (int i = 1; i < MAX_JOGADORES; i++) {
            if (ranking->jogadores[i].pontuacao < menorPontuacao) {
                menorPontuacao = ranking->jogadores[i].pontuacao;
                menorIndice = i;
            }
        }

        if (jogador.pontuacao > menorPontuacao) {
            ranking->jogadores[menorIndice] = jogador;
        }
    }

    ordenarRanking(ranking);
}

void ordenarRanking(Ranking *ranking) {
    for (int i = 0; i < ranking->qtdJogadores - 1; i++) {
        for (int j = 0; j < ranking->qtdJogadores - i - 1; j++) {
            if (ranking->jogadores[j].pontuacao < ranking->jogadores[j + 1].pontuacao) {
                Jogador temp = ranking->jogadores[j];
                ranking->jogadores[j] = ranking->jogadores[j + 1];
                ranking->jogadores[j + 1] = temp;
            }
        }
    }
}

void salvarRanking(Ranking *ranking, const char *arquivo) {
    ofstream file(arquivo);
    if (!file.is_open()) return;

    file << ranking->qtdJogadores << "\n";

    for (int i = 0; i < ranking->qtdJogadores; i++) {
        file << ranking->jogadores[i].nome << "\n";
        file << ranking->jogadores[i].data << "\n";
        file << ranking->jogadores[i].pontuacao << "\n";
        file << ranking->jogadores[i].tempoJogado << "\n";
        file << ranking->jogadores[i].vidas << "\n";
    }

    file.close();
}

void carregarRanking(Ranking *ranking, const char *arquivo) {
    ifstream file(arquivo);
    if (!file.is_open()) {
        inicializarRanking(ranking);
        return;
    }

    file >> ranking->qtdJogadores;
    file.ignore();

    if (ranking->qtdJogadores > MAX_JOGADORES) {
        ranking->qtdJogadores = MAX_JOGADORES;
    }

    for (int i = 0; i < ranking->qtdJogadores; i++) {
        file.getline(ranking->jogadores[i].nome, 50);
        file.getline(ranking->jogadores[i].data, 20);
        file >> ranking->jogadores[i].pontuacao;
        file >> ranking->jogadores[i].tempoJogado;
        file >> ranking->jogadores[i].vidas;
        file.ignore();
    }

    file.close();
}

void desenharRanking(Ranking *ranking) {
    // FUNDO PRETO
    ClearBackground(DARKGRAY);

    // TÍTULO EM VERMELHO
    DrawText("RANKING", SCREEN_WIDTH / 2 - 100, 30, 50, BLACK);
    DrawText("RANKING", SCREEN_WIDTH / 2 - 100 + 3, 30 + 3, 50, RED);

    // LETRAS BRANCAS
    DrawText("Posicao", 50, 100, 20, BLACK);
    DrawText("Nome", 150, 100, 20, BLACK);
    DrawText("Pontos", 350, 100, 20, BLACK);
    DrawText("Tempo", 470, 100, 20, BLACK);
    DrawText("Data", 580, 100, 20, BLACK);

    DrawLine(40, 125, SCREEN_WIDTH - 40, 125, BLACK);

    for (int i = 0; i < ranking->qtdJogadores && i < 8; i++) {
        int y = 140 + i * 40;

        DrawText(TextFormat("%d", i + 1), 80, y, 20, BLACK);
        DrawText(ranking->jogadores[i].nome, 150, y, 20, BLACK);
        DrawText(TextFormat("%d", ranking->jogadores[i].pontuacao), 350, y, 20, BLACK);
        DrawText(TextFormat("%ds", ranking->jogadores[i].tempoJogado), 470, y, 20, BLACK);
        DrawText(ranking->jogadores[i].data, 580, y, 16, BLACK);
    }

    if (ranking->qtdJogadores == 0) {
        DrawText("Nenhum registro ainda!", SCREEN_WIDTH / 2 - 120, 250, 25, BLACK);
    }

    DrawText("Pressione ESC para voltar", 
             SCREEN_WIDTH / 2 - 140, 
             SCREEN_HEIGTH - 40, 
             20, 
             BLACK);
}
