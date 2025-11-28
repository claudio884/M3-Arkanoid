#include "../header/sons.h"
#include <cmath>
#include <cstdio>

// ----------------------------------------------------------------------
// Variáveis de música (globais internas ao módulo)
// ----------------------------------------------------------------------
Music musicaFase1;
Music musicaFase2;
Music musicaFase3;
Music *musicaAtual = NULL;

// ----------------------------------------------------------------------
// Inicializar sons e músicas
// ----------------------------------------------------------------------
void inicializarSons(Sons *sons) {
    InitAudioDevice();

    // ---------------------------------------------------------
    // 🔊 SONS CURTOS (colisão, item, vida, etc)
    // ---------------------------------------------------------

    // Colisão com a barra
    Wave waveColisaoBarra = {0};
    waveColisaoBarra.frameCount = 2205;
    waveColisaoBarra.sampleRate = 44100;
    waveColisaoBarra.sampleSize = 16;
    waveColisaoBarra.channels = 1;
    waveColisaoBarra.data = (short*)RL_MALLOC(waveColisaoBarra.frameCount * sizeof(short));

    for (unsigned int i = 0; i < waveColisaoBarra.frameCount; i++) {
        float t = (float)i / 44100.0f;
        float freq = 600.0f + t * 200.0f;
        float envelope = 1.0f - (t * 20.0f);
        if (envelope < 0) envelope = 0;
        ((short*)waveColisaoBarra.data)[i] =
            (short)(25000.0f * envelope * sinf(2.0f * PI * freq * t));
    }
    sons->colisaoBarra = LoadSoundFromWave(waveColisaoBarra);
    UnloadWave(waveColisaoBarra);
    SetSoundVolume(sons->colisaoBarra, 0.4f);

    // Colisão com Tijolo
    Wave waveColisaoTijolo = {0};
    waveColisaoTijolo.frameCount = 1470;
    waveColisaoTijolo.sampleRate = 44100;
    waveColisaoTijolo.sampleSize = 16;
    waveColisaoTijolo.channels = 1;
    waveColisaoTijolo.data = (short*)RL_MALLOC(waveColisaoTijolo.frameCount * sizeof(short));

    for (unsigned int i = 0; i < waveColisaoTijolo.frameCount; i++) {
        float t = (float)i / 44100.0f;
        float freq = 800.0f - t * 400.0f;
        float envelope = 1.0f - (t * 30.0f);
        if (envelope < 0) envelope = 0;
        ((short*)waveColisaoTijolo.data)[i] =
            (short)(28000.0f * envelope * sinf(2.0f * PI * freq * t));
    }
    sons->colisaoTijolo = LoadSoundFromWave(waveColisaoTijolo);
    UnloadWave(waveColisaoTijolo);
    SetSoundVolume(sons->colisaoTijolo, 0.4f);

    // Item coletado
    Wave waveItemColetado = {0};
    waveItemColetado.frameCount = 3675;
    waveItemColetado.sampleRate = 44100;
    waveItemColetado.sampleSize = 16;
    waveItemColetado.channels = 1;
    waveItemColetado.data = (short*)RL_MALLOC(waveItemColetado.frameCount * sizeof(short));

    for (unsigned int i = 0; i < waveItemColetado.frameCount; i++) {
        float t = (float)i / 44100.0f;
        float freq1 = 523.0f + t * 400.0f;
        float freq2 = 659.0f + t * 500.0f;
        float envelope = 1.0f - (t * 12.0f);
        if (envelope < 0) envelope = 0;
        ((short*)waveItemColetado.data)[i] =
            (short)(20000.0f * envelope * (sinf(2.0f * PI * freq1 * t) +
                                           sinf(2.0f * PI * freq2 * t)) / 2.0f);
    }
    sons->itemColetado = LoadSoundFromWave(waveItemColetado);
    UnloadWave(waveItemColetado);
    SetSoundVolume(sons->itemColetado, 0.5f);

    // Perdeu vida
    Wave wavePerdeuVida = {0};
    wavePerdeuVida.frameCount = 8820;
    wavePerdeuVida.sampleRate = 44100;
    wavePerdeuVida.sampleSize = 16;
    wavePerdeuVida.channels = 1;
    wavePerdeuVida.data = (short*)RL_MALLOC(wavePerdeuVida.frameCount * sizeof(short));

    for (int i = 0; i < wavePerdeuVida.frameCount; i++) {
        ((short*)wavePerdeuVida.data)[i] =
            (short)(32000.0f * sinf(2.0f * PI * 220.0f * i / 44100.0f));
    }
    sons->perdeuVida = LoadSoundFromWave(wavePerdeuVida);
    UnloadWave(wavePerdeuVida);
    SetSoundVolume(sons->perdeuVida, 0.5f);

    // Fase completa
    Wave waveFaseCompleta = {0};
    waveFaseCompleta.frameCount = 8820;
    waveFaseCompleta.sampleRate = 44100;
    waveFaseCompleta.sampleSize = 16;
    waveFaseCompleta.channels = 1;
    waveFaseCompleta.data = (short*)RL_MALLOC(waveFaseCompleta.frameCount * sizeof(short));

    for (int i = 0; i < waveFaseCompleta.frameCount; i++) {
        float freq = 880.0f + (i / 100.0f);
        ((short*)waveFaseCompleta.data)[i] =
            (short)(32000.0f * sinf(2.0f * PI * freq * i / 44100.0f));
    }
    sons->faseCompleta = LoadSoundFromWave(waveFaseCompleta);
    UnloadWave(waveFaseCompleta);
    SetSoundVolume(sons->faseCompleta, 0.5f);


    // -------------------------------------------------------------------
    // 🎵 TRÊS MÚSICAS DE FUNDO (1 POR FASE)
    // -------------------------------------------------------------------
    musicaFase1 = LoadMusicStream("sons/musica_fase1.wav");
    musicaFase2 = LoadMusicStream("sons/musica_fase2.wav");
    musicaFase3 = LoadMusicStream("sons/musica_fase3.wav");

    musicaFase1.looping = true;
    musicaFase2.looping = true;
    musicaFase3.looping = true;

    SetMusicVolume(musicaFase1, 0.35f);
    SetMusicVolume(musicaFase2, 0.35f);
    SetMusicVolume(musicaFase3, 0.35f);
}

// ----------------------------------------------------------------------
// Tocar música correspondente à fase
// ----------------------------------------------------------------------
void tocarMusicaPorFase(int fase) {
    if (musicaAtual != NULL)
        StopMusicStream(*musicaAtual);

    switch (fase) {
        case 1: musicaAtual = &musicaFase1; break;
        case 2: musicaAtual = &musicaFase2; break;
        case 3: musicaAtual = &musicaFase3; break;
    }

    PlayMusicStream(*musicaAtual);
}

// ----------------------------------------------------------------------
// ATUALIZAR música (obrigatório no loop do jogo)
// ----------------------------------------------------------------------
void atualizarMusicaFundo(Sons *sons) {
    if (musicaAtual != NULL)
        UpdateMusicStream(*musicaAtual);
}

// ----------------------------------------------------------------------
// DESCARREGAR sons e músicas
// ----------------------------------------------------------------------
void descarregarSons(Sons *sons) {
    UnloadSound(sons->colisaoBarra);
    UnloadSound(sons->colisaoTijolo);
    UnloadSound(sons->itemColetado);
    UnloadSound(sons->perdeuVida);
    UnloadSound(sons->faseCompleta);

    UnloadMusicStream(musicaFase1);
    UnloadMusicStream(musicaFase2);
    UnloadMusicStream(musicaFase3);

    CloseAudioDevice();
}

// ----------------------------------------------------------------------
// FUNÇÕES CURTAS
// ----------------------------------------------------------------------
void tocarSomColisaoBarra(Sons *sons)  { PlaySound(sons->colisaoBarra); }
void tocarSomColisaoTijolo(Sons *sons)  { PlaySound(sons->colisaoTijolo); }
void tocarSomItemColetado(Sons *sons)  { PlaySound(sons->itemColetado); }
void tocarSomPerdeuVida(Sons *sons)    { PlaySound(sons->perdeuVida); }
void tocarSomFaseCompleta(Sons *sons)  { PlaySound(sons->faseCompleta); }

// ----------------------------------------------------------------------
// OPÇÃO 1 — Adição das funções ausentes (compatibilidade com seu jogo.cpp)
// ----------------------------------------------------------------------
void tocarMusicaFundo(Sons *sons) {
    // Começa com música da fase 1 por padrão
    tocarMusicaPorFase(1);
}

void pararMusicaFundo(Sons *sons) {
    if (musicaAtual != NULL)
        StopMusicStream(*musicaAtual);
}
