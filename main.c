

#include "includes.h"

// Driver code
int main() {
    // Leitura da dimensão do SL
    int n;
    scanf("%d", &n);

    // Criação das váriaveis que vão conter o SL: Ax = b original
    // ATENÇÂO: Estas variáveis NÃO devem ser modificadas
    double** Ao = createMatrix(n, n); // Matriz A terá dimensão n x n
    double* Bo = createVector(n);

    // Leitura dos elementos do SL
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { // Lê os elementos para A
            scanf("%lf", &Ao[i][j]);
        }
        scanf("%lf", &Bo[i]); // Lê o último elemento de cada linha para b
    }

    // Criação dos vetores de solução(x), residuos(r), e dos auxiliares A e b
    double** A = createMatrix(n, n);
    double* b = createVector(n);
    double* x = createVector(n);
    double* r = createVector(n);

    // Inicializar x e r com zeros
    initVector(x, 0.0, n);
    initVector(r, 0.0, n);

    // Variáveis de retorno:
    int iter_count = 0; // Número de iterações do Gauss-Seidel
    int noUniqueSol = 0; // se noUniqueSol == 0, solução única. ==1, solução infinita, ==2, sem solução
    double time = 0.0; // Armazena tempo de execução

    LIKWID_MARKER_INIT;
   
    resetToOrignals(A, Ao, b, Bo, n);  // Copia o SL original para os auxiliares A e b


    //Eliminação de Gauss
    LIKWID_MARKER_START("EG_clássico");  // Instrumentação LIKWID e medida de tempo
    time = timestamp();
    gaussian(A, b, x, n, &noUniqueSol);
    time = timestamp() - time;
    LIKWID_MARKER_STOP("EG_clássico");

    resetToOrignals(A, Ao, b, Bo, n);   // Reseta os auxiliares Para calcular residuais, e para prox metodo
    calcResiduals(A, x, b, r, n);
    printf("\nEG clássico:\n");
    printSolution(x, r, n, time, noUniqueSol);


    // Gauss-Seidel
    initVector(x, 0.0, n); // Reseta o vetor solução para o próximo método

    LIKWID_MARKER_START("GS_clássico");
    time = timestamp();
    gaussSeidel(A, b, x, n, &iter_count);
    time = timestamp() - time;
    LIKWID_MARKER_STOP("GS_clássico");

    resetToOrignals(A, Ao, b, Bo, n); 
    calcResiduals(A, x, b, r, n);
    printf("GS clássico [%d iterações]:\n", iter_count);
    printSolution(x, r, n, time, noUniqueSol);


    // Eliminação Gaussiana 3-diagonal
    initVector(x, 0.0, n);

    LIKWID_MARKER_START("EG_3-diagonal");
    time = timestamp();
    triGaussian(A, b, x, n);
    time = timestamp() - time;
    LIKWID_MARKER_STOP("EG_3-diagonal");

    resetToOrignals(A, Ao, b, Bo, n); 
    calcResiduals(A, x, b, r, n);
    printf("EG 3-diagonal:\n");
    printSolution(x, r, n, time, noUniqueSol);

    // Gauss-Seidel 3-Diagonal
    initVector(x, 0.0, n);
    
    LIKWID_MARKER_START("GS_3-diagonal");
    time = timestamp();
    triSeidel(A, b, x, n, &iter_count);
    time = timestamp() - time;
    LIKWID_MARKER_STOP("GS_3-diagonal");
    
    resetToOrignals(A, Ao, b, Bo, n);
    calcResiduals(A, x, b, r, n);
    printf("GS 3-diagonal [%d iterações]:\n", iter_count);
    printSolution(x, r, n, time, noUniqueSol);


    LIKWID_MARKER_CLOSE;

    // Desalocação da memória
    destroyMatrix(Ao, n);
    destroyMatrix(A, n);
    free(Bo);
    free(b);
    free(x);
    free(r);
    
    return 0;
}
