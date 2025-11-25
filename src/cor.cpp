#include "../header/cor.h"

Color obterCorTijolo(int vida) {
    if (vida <= 0) return (Color){0, 0, 0, 0};
    if (vida == 1) return (Color){255, 165, 0, 255};
    if (vida == 2) return (Color){255, 0, 0, 255};
    return (Color){128, 0, 0, 255};
}

Color obterCorItem(int tipo) {
    if (tipo == 0) return (Color){0, 255, 0, 255};
    if (tipo == 1) return (Color){135, 206, 235, 255};
    if (tipo == 2) return (Color){0, 0, 139, 255};
    if (tipo == 3) return (Color){255, 215, 0, 255};
    if (tipo == 4) return (Color){128, 0, 128, 255};
    if (tipo == 5) return (Color){255, 192, 203, 255};
    return (Color){211, 211, 211, 255};
}
