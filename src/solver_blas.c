/*
 * Tema 3 ASC
 * 2025 Spring
 */
#include "utils.h"
#include <cblas.h>

/*
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B, double *x) {
    double *C = (double*)calloc(N * N, sizeof(double));
    double *Ct = (double*)calloc(N * N, sizeof(double));
    double *D = (double*)calloc(N * N, sizeof(double));
    double *y = (double*)calloc(N, sizeof(double));
    double *tmp_x = (double*)calloc(N, sizeof(double));

    // C = B * Aᵗ
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans,
                N, N, N, 1.0, B, N, A, N, 0.0, C, N);

    // Ct = Cᵗ — transpunem C manual pentru a o putea folosi în BLAS
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            Ct[j * N + i] = C[i * N + j];

    // D = Ct * A
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                N, N, N, 1.0, Ct, N, A, N, 0.0, D, N);

    // Copiem x în tmp_x pentru a putea lucra în loop
    for (int i = 0; i < N; ++i)
        tmp_x[i] = x[i];

    // Loop: for i = 0 to N-1
    for (int i = 0; i < N; ++i) {
        // y = Ct * x
        cblas_dgemv(CblasRowMajor, CblasNoTrans,
                    N, N, 1.0, Ct, N, tmp_x, 1, 0.0, y, 1);

        // x = C * y (scriem direct în tmp_x)
        cblas_dgemv(CblasRowMajor, CblasNoTrans,
                    N, N, 1.0, C, N, y, 1, 0.0, tmp_x, 1);
    }

    // y = D * x
    cblas_dgemv(CblasRowMajor, CblasNoTrans,
                N, N, 1.0, D, N, tmp_x, 1, 0.0, y, 1);

    // Clean up
    free(C);
    free(Ct);
    free(D);
    free(tmp_x);

    return y;
}