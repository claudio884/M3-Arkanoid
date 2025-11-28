#include "../header/cores.h"
#include "raylib.h"

// Tema INFERNO / LAVA / MAGMA

Color obterCorTijolo(int vida)
{
    // Lava profunda (vida 3)
    static Color vida3[] = {
        {160, 20, 20, 255},   // Vermelho escuro
        {180, 40, 10, 255},   // Magma denso
        {140, 10, 30, 255},   // Vermelho queimado
        {200, 30, 0, 255},    // Carmesim intenso
        {150, 0, 0, 255},     // Rubro quase preto
        {120, 15, 15, 255}    // Brasa apagada
    };

    // Lava derretida (vida 2)
    static Color vida2[] = {
        {255, 80, 20, 255},   // Lava viva
        {255, 100, 40, 255},  // Laranja incandescente
        {240, 70, 10, 255},   // Laranja fogo
        {255, 60, 0, 255},    // Fogo puro
        {230, 50, 0, 255},    // Lava explosiva
        {255, 90, 30, 255}    // Laranja magma
    };

    // Brasas (vida 1)
    static Color vida1[] = {
        {255, 180, 40, 255},  // Brasa forte
        {255, 160, 20, 255},  // Brasa dourada
        {255, 200, 60, 255},  // Fogo claro
        {240, 150, 0, 255},   // Amarelo quente
        {255, 170, 60, 255},  // Laranja queimado
        {230, 140, 10, 255}   // Brasa profunda
    };

    int seed = ((int)(GetTime() * 1000)) % 6;

    if (vida >= 3) return vida3[seed];
    if (vida == 2) return vida2[seed];
    if (vida == 1) return vida1[seed];

    return (Color){70, 40, 40, 255}; // Cinza avermelhado queimado
}


// Itens com tema de fogo e metal derretido
Color obterCorItem(int tipo)
{
    switch (tipo) {
        case 0: return (Color){255, 100, 50, 255};   // Laranja derretido
        case 1: return (Color){255, 180, 70, 255};   // Fogo claro
        case 2: return (Color){200, 60, 30, 255};    // Vermelho brasa
        case 3: return (Color){255, 220, 80, 255};   // Ouro incandescente
        case 4: return (Color){255, 150, 110, 255};  // Fumaça laranja
        case 5: return (Color){100, 40, 40, 255};    // Cinza queimado / carvão
        default: return WHITE;
    }
}
