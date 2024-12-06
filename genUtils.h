/*******************************************
EP01 - Introdução à Computação Ciêntífica
Fabiano A. de Sá Filho
GRR 20223831
07/04/2024
*******************************************/

#ifndef GEN_UTILS_H
#define GEN_UTILS_H

double* createVector(int n);
double** createMatrix(int linhas, int colunas);
void calcResiduals(double **A, double *x, double *b, double *r, int n);
void copyVector(double *dest, double *src, int n);
void destroyMatrix(double** matriz, int linhas);
void printVector(double *vec, int n);
void initVector(double *x, double initialValue, int n);
void copyMatrix(double **A, double **Aoriginal, int rows, int cols);
void printSolution(double *x, double *r, int n, double time_ms, int status);
void resetToOrignals(double **A, double **Aoriginal, double* b, double* Bo, int n);

#endif //GEN_UTILS_H