#include "../header/graficos.h"
#include "../header/constantes.h"
#include <cmath>

// ------------------------------------------
// FUNÇÃO PRINCIPAL DE DESENHO DO FUNDO
// ------------------------------------------
void desenharFundo(int fase, float tempo) {
    if (fase == 1) {
        desenharFundoForja(tempo);
    } 
    else if (fase == 2) {
        desenharFundoVulcao(tempo);
    } 
    else {
        desenharFundoAbismo(tempo);
    }
}

// ==========================================
// ============= FASE 1 – FORJA =============
// ==========================================
void desenharFundoForja(float tempo) {

    // GRADIENTE DE AÇO QUENTE
    for (int y = 0; y < SCREEN_HEIGTH; y += 2) {
        float t = (float)y / SCREEN_HEIGTH;
        int r = (int)(60 + t * 100);   // metal avermelhado
        int g = (int)(30 + t * 40);
        int b = (int)(20 + t * 20);
        DrawRectangle(0, y, SCREEN_WIDTH, 2, (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, 255});
    }

    // FAÍSCAS SUBINDO
    for (int i = 0; i < 40; i++) {
        int seed = i * 3571;
        int x = (seed * 83) % SCREEN_WIDTH;
        float subida = fmodf(tempo * 120.0f + i * 25.0f, (float)SCREEN_HEIGTH);
        int y = SCREEN_HEIGTH - (int)subida;

        DrawCircle(x, y, 2 + (seed % 3), (Color){255, 200, 80, (unsigned char)(150 + (seed % 80))});
    }

    // CHÃO DE FERRO QUENTE
    DrawRectangle(0, SCREEN_HEIGTH - 50, SCREEN_WIDTH, 50, (Color){120, 60, 40, 255});
}


// ==========================================
// ============= FASE 2 – VULCÃO ============
// ==========================================
void desenharFundoVulcao(float tempo) {

    // GRADIENTE VERMELHO/ESCURIDÃO
    for (int y = 0; y < SCREEN_HEIGTH; y += 2) {
        float t = (float)y / SCREEN_HEIGTH;
        float pulso = sinf(tempo * 1.5f) * 8.0f;
        int r = (int)(100 + t * 80 + pulso);
        int g = (int)(20 + t * 20);
        int b = (int)(20 + t * 20);

        DrawRectangle(0, y, SCREEN_WIDTH, 2,
            (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, 255});
    }

    // PARTÍCULAS DE LAVA SUBINDO
    for (int i = 0; i < 35; i++) {
        int seed = i * 5147;
        int x  = (seed * 131) % SCREEN_WIDTH;
        int tam = 5 + (seed % 8);
        float movimento = fmodf(tempo * 35.0f + i * 12.0f, (float)SCREEN_HEIGTH);
        int yFinal = SCREEN_HEIGTH - (int)movimento;

        DrawCircle(x, yFinal, tam, (Color){255, 90, 0, (unsigned char)(130 + (seed % 120))});
    }

    // CHÃO ROCHOSO
    DrawRectangle(0, SCREEN_HEIGTH - 60, SCREEN_WIDTH, 60, (Color){70, 30, 25, 255});
}


// ==========================================
// ======== FASE 3 – ABISMO INFERNAL ========
// ==========================================
void desenharFundoAbismo(float tempo) {

    // GRADIENTE DE ROXO → PRETO (profundidade demoníaca)
    for (int y = 0; y < SCREEN_HEIGTH; y += 2) {
        float t = (float)y / SCREEN_HEIGTH;

        int r = (int)(40 + t * 10);
        int g = (int)(10 + t * 5);
        int b = (int)(50 + t * 50);

        DrawRectangle(0, y, SCREEN_WIDTH, 2,
            (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, 255});
    }

    // CHAMAS AZUIS FLUTUANDO
    for (int i = 0; i < 25; i++) {
        int seed = i * 8291;

        int x = (seed * 97) % SCREEN_WIDTH;
        int tam = 12 + (seed % 6);

        float flutua = sinf(tempo * 2.0f + i) * 20.0f;
        int y = 120 + (seed % 250) + (int)flutua;

        DrawCircle(x, y, tam,
            (Color){80, 160, 255, (unsigned char)(120 + (seed % 100))});
    }

    // ROCHA OBSIDIANA
    DrawRectangle(0, SCREEN_HEIGTH - 70, SCREEN_WIDTH, 70, (Color){20, 10, 20, 255});

    // RACHADURAS COM FOGO AZUL
    for (int i = 0; i < 12; i++) {
        int seed = i * 6113;
        int x = (seed * 71) % SCREEN_WIDTH;
        int y = SCREEN_HEIGTH - 70 + (seed % 40);

        int brilho = (int)(((sinf(tempo * 3.0f + i * 0.4f) + 1.0f) / 2.0f) * 180);

        DrawEllipse(x, y, 16, 6, (Color){40, 20, 60, 255});
        DrawEllipse(x, y, 9, 3, (Color){80, 140, 255, (unsigned char)brilho});
    }
}
