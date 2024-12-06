

#ifndef HELPERS_H
#define HELPERS_H

void splitTridiagonalMatrix(double **A, double *lower, double *main, double *upper, int n);
double maxNorm(double *x, double *oldX, int n);
void swapRows(double **A, double *b, int row1, int row2, int n);
int isRowZero(double *row, int n);
int findPivotRow(double **A, int col, int n);


#endif //HELPERS_H
