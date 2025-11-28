#ifndef BARRA_H
#define BARRA_H

struct Posicao {
       float x;
       float y;
};

struct Barra {
    Posicao posicao; 
    float largura;
    float altura;
    float velocidadeX;
};

void inicializarBarra(Barra *barra);

void atualizarBarra(Barra *barra, float dt);

void desenharBarra(Barra *barra);

void aumentarTamanhoBarra(Barra *barra, float tamanhoAdd);

void diminuirTamanhoBarra(Barra *barra, float tamanhoSub);

#endif
