#include "../header/jogador.h"
#include "../header/constantes.h"
#include <cstring>
#include <ctime>

void inicializarJogador(Jogador *jogador, const char *nome) {
    strncpy(jogador->nome, nome, 49);
    jogador->nome[49] = '\0';
    

    time_t agora = time(0);
    struct tm *tempoAgora = localtime(&agora);
    
    if (tempoAgora != nullptr) {
        strftime(jogador->data, 20, "%d/%m/%Y %H:%M", tempoAgora);
    } else {
        strncpy(jogador->data, "00/00/0000 00:00", 19);
        jogador->data[19] = '\0';
    }
    
    jogador->pontuacao = 0;
    jogador->tempoJogado = 0;
    jogador->vidas = VIDAS_INICIAIS;
}

void atualizarPontuacao(Jogador *jogador, int pontos) {
    jogador->pontuacao += pontos;
    if (jogador->pontuacao < 0) {
        jogador->pontuacao = 0;
    }
}

void adicionarVida(Jogador *jogador) {
    jogador->vidas++;
    if (jogador->vidas > 9) {
        jogador->vidas = 9;
    }
}

void removerVida(Jogador *jogador) {
    if (jogador->vidas > 0) {
        jogador->vidas--;
    }
}

void atualizarTempo(Jogador *jogador, int segundos) {
    jogador->tempoJogado = segundos;
}
