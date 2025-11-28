#include "../header/utils.h"
#include "../header/tijolo.h"
#include <cstdlib>

template<typename T>
T maximo(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T>
T minimo(T a, T b) {
    return (a < b) ? a : b;
}

template<typename T>
void trocar(T *a, T *b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template int maximo<int>(int, int);
template float maximo<float>(float, float);
template int minimo<int>(int, int);
template float minimo<float>(float, float);
template void trocar<int>(int*, int*);
template void trocar<float>(float*, float*);

int* alocarArrayInt(int tamanho) {
    int *arr = (int*)malloc(tamanho * sizeof(int));
    if (arr != NULL) {
        for (int i = 0; i < tamanho; i++) {
            arr[i] = 0;
        }
    }
    return arr;
}

float* alocarArrayFloat(int tamanho) {
    float *arr = (float*)malloc(tamanho * sizeof(float));
    if (arr != NULL) {
        for (int i = 0; i < tamanho; i++) {
            arr[i] = 0.0f;
        }
    }
    return arr;
}

void liberarArray(int *arr) {
    if (arr != NULL) {
        free(arr);
    }
}

void liberarArray(float *arr) {
    if (arr != NULL) {
        free(arr);
    }
}

int somarRecursivo(int n) {
    if (n <= 0) {
        return 0;
    }
    return n + somarRecursivo(n - 1);
}

int calcularPontosRecursivo(int tijolo, int multiplicador) {
    if (tijolo <= 0) {
        return 0;
    }
    return (10 * multiplicador) + calcularPontosRecursivo(tijolo - 1, multiplicador);
}

int contarTijolosRecursivo(Tijolo *tijolos, int inicio, int fim) {
    if (inicio > fim) {
        return 0;
    }

    int count = tijolos[inicio].ativo ? 1 : 0;
    return count + contarTijolosRecursivo(tijolos, inicio + 1, fim);
}

void ordenarPontosRecursivo(int *pontos, int inicio, int fim) {
    if (inicio >= fim) {
        return;
    }
    
    int pivo = pontos[fim];
    int i = inicio - 1;
    
    for (int j = inicio; j < fim; j++) {
        if (pontos[j] > pivo) {
            i++;
            trocar(&pontos[i], &pontos[j]);
        }
    }
    
    trocar(&pontos[i + 1], &pontos[fim]);
    int pivoPos = i + 1;
    
    ordenarPontosRecursivo(pontos, inicio, pivoPos - 1);
    ordenarPontosRecursivo(pontos, pivoPos + 1, fim);
}

int calcularFatorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * calcularFatorial(n - 1);
}
