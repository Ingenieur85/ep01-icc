
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> 

#include "utils.h"
#include "genUtils.h"
#include "helpers.h"
#include "gaussian.h"

// Algoritmo de eliminação Gaussiana
void gaussianElimination(double **A, double *b, int n, int *status) {
    *status = 0; // Inicializa o status como 0, assumindo que o sistema pode ter uma solução única

    for (int i = 0; i < n; i++) {
        int pivotRow = findPivotRow(A, i, n); // Encontra a linha pivô para a coluna atual 'i'

        // Verifica se o elemento pivô é zero (potencialmente indica infinitas soluções)
        if (A[pivotRow][i] == 0) {
            *status = 1; // Atualiza o status para 1
            return;
        }

        swapRows(A, b, i, pivotRow, n); // Troca a linha atual com a linha pivô

        // Loop para aplicar a eliminação nas linhas abaixo da linha atual
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i]; // Calcula o fator de multiplicação para a eliminação

            // Realiza a eliminação Gaussiana nas colunas restantes
            for (int k = i; k < n; k++) {
                A[j][k] -= A[i][k] * factor; // Atualiza os elementos da matriz A
            }
            b[j] -= b[i] * factor; // Atualiza o vetor b correspondente

            // Verifica a consistência do sistema após a eliminação
            if (j > i && isRowZero(A[j], n) && b[j] != 0) {
                *status = 2; // Atualiza o status para 2, indicando um sistema sem solução
                return;
            }
        }
    }
}

// Função que executa a eliminação Gaussiana com retro substituição e pivoteamento parcial
void gaussian(double **A, double *b, double *x, unsigned int n, int *status) {
    // Inicializa o vetor solução 'x' com zeros
    initVector(x, 0.0, n);

    // Executa o algoritmo de eliminação gaussiana para colocar o sistema na forma escalonada
    gaussianElimination(A, b, n, status);

    // Retro substituição: calcula as soluções do sistema a partir da última linha para a primeira
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i]; // Inicializa o valor de x[i] com o correspondente valor em b

        // Subtrai o valor das variáveis já calculadas das linhas subsequentes
        for (uint j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j]; // Ajusta x[i] com base nos valores já encontrados de x[j]
        }

        x[i] /= A[i][i]; // Divide pelo coeficiente da diagonal para isolar x[i]
    }
}

