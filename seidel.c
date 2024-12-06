
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "helpers.h"
#include "utils.h"
#include "genUtils.h"
#include "seidel.h"

#define TOLERANCE 1e-4  // Define a tolerância para o critério de convergência
#define MAX_ITER 50     // Define o número máximo de iterações

// Método de Gauss-Seidel
void gaussSeidel(double **A, double *b, double *x, int n, int *iter_count) {
    initVector(x, 0.0, n);  // Inicializa o vetor x com zeros
    double *oldX = createVector(n); // Armazena os valores da iteração passada
    *iter_count = 0;  // Inicializa a contagem de iterações

    for (int iter = 0; iter < MAX_ITER; iter++) {
        (*iter_count)++; 

        for (int i = 0; i < n; i++) {
            oldX[i] = x[i];  // Armazena os valores de x para verificar a convergência
        }

        for (int i = 0; i < n; i++) {
            double sigma = 0.0; // Variável para acumular a soma dos termos A[i][j] * x[j]
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sigma += A[i][j] * x[j]; // Soma os termos, excluindo o elemento da diagonal
                }
            }
            x[i] = (b[i] - sigma) / A[i][i]; // Atualiza x[i] com o novo valor
        }

        // Convergência: Se a norma máxima da diferença for menor que a tolerância, interrompe
        if (maxNorm(x, oldX, n) < TOLERANCE) {
            break; 
        }
    }

    free(oldX);
}
