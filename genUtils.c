

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> 

#include "utils.h"
#include "genUtils.h"

// Aloca memória para un array de n posições
double* createVector(int n) {
    double* v = (double*)malloc(n * sizeof(double));
    if (!v) {
        perror("Erro ao alocar vetor");
        return NULL;
    }

    return v;
}

// Função para criar e alocar uma matriz dinamicamente
double** createMatrix(int linhas, int colunas) {
    double** matriz = (double**)malloc(linhas * sizeof(double*));
    if (!matriz){
        perror("Erro ao alocar matriz");
        return NULL;
    }
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (double*)malloc(colunas * sizeof(double));
    }
    return matriz;
}

// Copia conteúdo de src para dst. Assume dest foi alocado por quem chamou.
void copyVector(double *dest, double *src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Função para desalocar a memória da matriz
void destroyMatrix(double** matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}
// Print Vector
void printVector(double *vec, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.12f\t", vec[i]);
    }
    printf("\n");
}

// Seta todas as posições de *x para initValue
void initVector(double *x, double initialValue, int n) {
    for (int i = 0; i < n; i++) {
        x[i] = initialValue;
    }
}

// Copia os conteúdos de Aoriginal para A. Assume A foi alocado por quem chamou
void copyMatrix(double **A, double **Aoriginal, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A[i][j] = Aoriginal[i][j];
        }
    }
}

// Calcula residuas na forma r = b -Ax, onde b e A são do sistema ORIGINAL
// ATENÇÃO: Chamar somente após copiar SL original para A e b
void calcResiduals(double **A, double *x, double *b, double *r, int n) {
    for (int i = 0; i < n; i++) {
        r[i] = -b[i];
        for (int j = 0; j < n; j++) {
            r[i] += A[i][j] * x[j];
        }
    }
}

// Função imprime resultado do SL
void printSolution(double *x, double *r, int n, double time_ms, int status) {
    printf("%.8f ms\n", time_ms);

    if (status == 0) {
        //printf("Solution (y):\n");
        printVector(x, n);
        //printf("Residuals (r):\n");
        printVector(r, n);
    } else if (status == 1) {
        printf("O sistema linear tem infinitas soluções.\n");
    } else if (status == 2) {
        printf("O sistema linear fornecido não possuí solução.\n");
    }

    printf("\n");
}

// Copia o SL original para as variaveis auxiliares
void resetToOrignals(double **A, double **Aoriginal, double* b, double* Bo, int n) {
    copyMatrix(A, Aoriginal, n, n);
    copyVector(b, Bo, n);
}