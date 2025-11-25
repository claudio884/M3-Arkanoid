#include <string.h>
#include <stdio.h>
#include "../header/menu.h"
#include "../header/estadoJogo.h"
#include "../header/constante.h"

void inicializarMenu(Menu *menu) {
    menu->opcao = 0;
    menu->totalOpcoes = 3;
    menu->tamanhoNome = 0;
    menu->nomeJogador[0] = '\0';
}

void desenharMenuPrincipal(Menu *menu) {
    const char *opcoes[3] = {
        "Iniciar Jogo",
        "Dificuldade",
        "Pontuacao/Rank"
    };
    
    for (int i = 0; i < 3; i++) {
        if (i == menu->opcao) {
            printf(">>> %s <<<\n", opcoes[i]);
        } else {
            printf("    %s\n", opcoes[i]);
        }
    }
}

void desenharMenuDificuldade(Menu *menu) {
    const char *dificuldades[3] = {
        "Facil",
        "Medio",
        "Dificil"
    };
    
    printf("\n=== DIFICULDADE ===\n");
    for (int i = 0; i < 3; i++) {
        if (i == menu->opcao) {
            printf(">>> %s <<<\n", dificuldades[i]);
        } else {
            printf("    %s\n", dificuldades[i]);
        }
    }
}

void desenharMenuRegistro(Menu *menu) {
    printf("\n=== NOME DO JOGADOR ===\n");
    printf("Digite seu nome: %s\n", menu->nomeJogador);
}

void desenharMenuGameOver(Menu *menu, int pontuacao, int tempo) {
    printf("\n=== GAME OVER ===\n");
    printf("Pontos: %d\n", pontuacao);
    printf("Tempo: %d segundos\n", tempo);
    printf("Pressione ENTER para voltar ao menu\n");
}

void desenharMenuVitoria(Menu *menu, int pontuacao, int tempo) {
    printf("\n=== VITORIA! ===\n");
    printf("Pontos: %d\n", pontuacao);
    printf("Tempo: %d segundos\n", tempo);
    printf("Pressione ENTER para voltar ao menu\n");
}

void desenharMenuPausa(Menu *menu) {
    printf("\n=== PAUSA ===\n");
    printf("Pressione P para continuar\n");
}

int atualizarMenu(Menu *menu) {
    char entrada;
    printf("\nUse W/S para navegar, ENTER para selecionar: ");
    if (scanf("%c", &entrada) == 1) {
        if (entrada == 'w' || entrada == 'W') {
            menu->opcao = (menu->opcao - 1 + menu->totalOpcoes) % menu->totalOpcoes;
            printf("\n");
        } else if (entrada == 's' || entrada == 'S') {
            menu->opcao = (menu->opcao + 1) % menu->totalOpcoes;
            printf("\n");
        } else if (entrada == '\n' || entrada == ' ') {
            printf("\n");
            return 1;
        }
    }
    return 0;
}

bool atualizarMenuRegistro(Menu *menu) {
    char entrada[50];
    if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
        int len = strlen(entrada);
        if (len > 0 && entrada[len - 1] == '\n') {
            entrada[len - 1] = '\0';
        }
        if (strlen(entrada) > 0) {
            strncpy(menu->nomeJogador, entrada, sizeof(menu->nomeJogador) - 1);
            menu->nomeJogador[sizeof(menu->nomeJogador) - 1] = '\0';
            menu->tamanhoNome = strlen(menu->nomeJogador);
            return true;
        }
    }
    return false;
}
