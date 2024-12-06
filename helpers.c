

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> 

#include "utils.h"
#include "genUtils.h"
#include "helpers.h"

// Separa uma matriz 3-diagonal em vetores. Assume alocação por quem chamou
void splitTridiagonalMatrix(double **A, double *lower, double *main, double *upper, int n) {
    for (int i = 0; i < n; i++) {
        main[i] = A[i][i];
        if (i < n - 1) {
            upper[i] = A[i][i + 1];
            lower[i] = A[i + 1][i];
        }
    }
}

// Calcula a norma máxima entre vetor solução atual e da iteração anterior
double maxNorm(double *x, double *oldX, int n) {
    double max = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = fabs(x[i] - oldX[i]);
        if (diff > max) {
            max = diff;
        }
    }
    return max;
}

// Troca duas linhas da matriz aumentada. Manipula A e b diretamente.
void swapRows(double **A, double *b, int row1, int row2, int n) {
    if (row1 != row2) {
        for (int i = 0; i < n; i++) {
            double temp = A[row1][i];
            A[row1][i] = A[row2][i];
            A[row2][i] = temp;
        }
        double tempB = b[row1];
        b[row1] = b[row2];
        b[row2] = tempB;
    }
}

// Helper que confere se existe uma linha de zeros
int isRowZero(double *row, int n) {
    for (int i = 0; i < n; i++) {
        if (row[i] != 0) return 0;
    }
    return 1;
}

// Encontra a linha com o maio elemento para uma dada coluna
int findPivotRow(double **A, int col, int n) {
    int maxRow = col;
    double maxVal = fabs(A[col][col]);

    for (int i = col + 1; i < n; i++) {
        if (fabs(A[i][col]) > maxVal) {
            maxVal = fabs(A[i][col]);
            maxRow = i;
        }
    }
    return maxRow;
}