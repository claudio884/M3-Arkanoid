#include "../header/sons.h"

void inicializarSom(Sons* sons) {
    if (!sons) return;
    sons->musicaFundo = (Music){0};
    sons->somBarra = (Sound){0};
    sons->somTijolo = (Sound){0};
    sons->somItem = (Sound){0};
    sons->perdeVida = (Sound){0};
    sons->passouFase = (Sound){0};
}

void descarregarSons(Sons* sons) {
    if (!sons) return;
}

void somColisaoBarra(Sons* sons) {
    if (!sons) return;
}

void somItemColetado(Sons* sons) {
    if (!sons) return;
}

void somPerderVida(Sons* sons) {
    if (!sons) return;
}

void musicaFundo(Sons* sons) {
    if (!sons) return;
}

void pararMusicaFundo(Sons* sons) {
    if (!sons) return;
}

void atualizarMusicaFundo(Sons* sons) {
    if (!sons) return;
}
