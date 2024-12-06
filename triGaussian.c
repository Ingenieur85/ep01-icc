

#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"
#include "utils.h"
#include "genUtils.h"
#include "triGaussian.h"

#include <stdio.h>
#include <stdlib.h>

// Eliminação gaussiana específica para matrizes tridiagonais
void triGaussianElimination(double *d, double *a, double *c, double *b, double *x, unsigned int n) {
    // Eliminação para frente
    for (unsigned int i = 0; i < n - 1; ++i) {
        double m = a[i] / d[i]; // Calcula o multiplicador para a linha atual
        d[i + 1] -= c[i] * m;    // Atualiza o elemento principal na próxima linha
        b[i + 1] -= b[i] * m;    // Atualiza o vetor b com base no multiplicador
    }

    // Substituição para trás
    x[n - 1] = b[n - 1] / d[n - 1]; // Calcula o último elemento de x
    for (int i = n - 2; i >= 0; --i) {
        x[i] = (b[i] - c[i] * x[i + 1]) / d[i]; // Calcula os elementos restantes de x
    }
}

// Função auxiliar para a eliminação gaussiana tridiagonal
void triGaussian(double **A, double *b, double *x, unsigned int n) {
    double *lower = createVector(n-1);
    double *main = createVector(n);
    double *upper = createVector(n-1);

    // Divide a matriz tridiagonal em três vetores
    splitTridiagonalMatrix(A, lower, main, upper, n);

    // Chama o algoritimo de EG para tridiagonais
    triGaussianElimination(main, lower, upper, b, x, n);

    // Libera a memória alocada
    free(lower);
    free(main);
    free(upper);
}
