#ifndef UTILS_H
#define UTILS_H

template<typename T>
T maximo(T a, T b);

template<typename T>
T minimo(T a, T b);

template<typename T>
void trocar(T *a, T *b);

int* alocarArrayInt(int tamanho);

float* alocarArrayFloat(int tamanho);

void liberarArray(int *arr);

void liberarArray(float *arr);

int somarRecursivo(int n);

int calcularPontosRecursivo(int tijolos, int multiplicador);

int contarTijolosRecursivo(struct Tijolo *tijolos, int inicio, int fim);

void ordenarPontosRecursivo(int *pontos, int inicio, int fim);

int calcularFatorial(int n);

#endif
