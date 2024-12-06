

#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"
#include "utils.h"
#include "genUtils.h"
#include "triSeidel.h"

#define MAX_ITER 50
#define TOLERANCE 1e-4

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITER 50       // Número máximo de iterações
#define TOLERANCE 1e-4    // Tolerância para a convergência

// Algoritmo Gauss-Seidel otimizado para uma matriz tridiagonal
void triSeidel(double **A, double *b, double *x, int n, int *iter_count) {
    // Alocação de vetores para representar as diagonais da matriz tridiagonal
    double *lower = createVector(n-1); 
    double *main = createVector(n);   
    double *upper = createVector(n-1); 
    double *oldX = createVector(n); // Vetor para armazenar os valores da última iteração

    initVector(oldX, 0.0, n); // Inicializa oldX com zeros
    initVector(x, 0.0, n);  // Inicializa x com zeros
    *iter_count = 0;        // Inicializa a contagem de iterações em 0

    // Divide a matriz tridiagonal em três vetores
    splitTridiagonalMatrix(A, lower, main, upper, n);

    double error = TOLERANCE + 1.0;  // Inicia com um erro maior que a tolerância
    while (*iter_count < MAX_ITER && error > TOLERANCE) {
        (*iter_count)++;
        
        // Iteração Gauss-Seidel para matriz tridiagonal
        x[0] = (b[0] - upper[0] * x[1]) / main[0]; // Primeiro elemento
        for (int i = 1; i < n - 1; i++) {
            // Cálculo iterativo de x[i] considerando os elementos vizinhos
            x[i] = (b[i] - lower[i - 1] * x[i - 1] - upper[i] * x[i + 1]) / main[i];
        }
        // Cálculo do último elemento de x
        x[n - 1] = (b[n - 1] - lower[n - 2] * x[n - 2]) / main[n - 1];

        // Calcula a norma máxima da diferença (x - oldX) para verificar a convergência
        error = maxNorm(x, oldX, n);
        
        // Atualiza oldX para a próxima iteração
        for (int i = 0; i < n; i++) {
            oldX[i] = x[i];
        }
    }

    // Liberação da memória
    free(lower);
    free(main);
    free(upper);
    free(oldX);
}
