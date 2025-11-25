
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

int calcularPontosRecursivo(int blocos, int multiplicador);

int contarBlocosRecursivo(struct Bloco *blocos, int inicio, int fim);

void ordenarPontosRecursivo(int *pontos, int inicio, int fim);

int calcularFatorial(int n);

#endif
