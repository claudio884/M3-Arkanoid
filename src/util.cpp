#include <stdlib.h>
#include "../header/util.h"

template<typename T>
T maximo(T a, T b) {
    return a > b ? a : b;
}

template<typename T>
T minimo(T a, T b) {
    return a < b ? a : b;
}

template<typename T>
void trocar(T* a, T* b) {
    if (!a || !b) return;
    T temp = *a;
    *a = *b;
    *b = temp;
}

int* alocarArrayInt(int tamanho) {
    if (tamanho <= 0) return NULL;
    return (int*) malloc(sizeof(int) * tamanho);
}

float* alocarArrayFloat(int tamanho) {
    if (tamanho <= 0) return NULL;
    return (float*) malloc(sizeof(float) * tamanho);
}

void liberarArray(int* arr) {
    if (arr) free(arr);
}

void liberarArray(float* arr) {
    if (arr) free(arr);
}

int somarRecursivo(int n) {
    if (n <= 0) return 0;
    return n + somarRecursivo(n - 1);
}

int calcularPontosRecursivos(int tijolos, int multiplicador) {
    if (tijolos <= 0) return 0;
    return (tijolos * multiplicador) + calcularPontosRecursivos(tijolos - 1, multiplicador);
}

int contarTijolosRecursivos(Tijolo* tijolos, int inicio, int fim) {
    if (!tijolos || inicio > fim) return 0;
    if (inicio == fim) return tijolos[inicio].ativo ? 1 : 0;
    int meio = (inicio + fim) / 2;
    return contarTijolosRecursivos(tijolos, inicio, meio) + 
           contarTijolosRecursivos(tijolos, meio + 1, fim);
}

void ordenarPontosRecursivos(int* pontos, int inicio, int fim) {
    if (!pontos || inicio >= fim) return;
    
    int meio = (inicio + fim) / 2;
    ordenarPontosRecursivos(pontos, inicio, meio);
    ordenarPontosRecursivos(pontos, meio + 1, fim);
    
    int* temp = (int*) malloc(sizeof(int) * (fim - inicio + 1));
    if (!temp) return;
    
    int i = inicio, j = meio + 1, k = 0;
    while (i <= meio && j <= fim) {
        if (pontos[i] >= pontos[j]) {
            temp[k++] = pontos[i++];
        } else {
            temp[k++] = pontos[j++];
        }
    }
    
    while (i <= meio) temp[k++] = pontos[i++];
    while (j <= fim) temp[k++] = pontos[j++];
    
    for (i = inicio, k = 0; i <= fim; i++, k++) {
        pontos[i] = temp[k];
    }
    
    free(temp);
}

int calcularFatorial(int n) {
    if (n <= 1) return 1;
    return n * calcularFatorial(n - 1);
}

template int maximo<int>(int a, int b);
template float maximo<float>(float a, float b);
template int minimo<int>(int a, int b);
template float minimo<float>(float a, float b);
template void trocar<int>(int* a, int* b);
template void trocar<float>(float* a, float* b);
