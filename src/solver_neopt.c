/*
 * Tema 2 ASC
 * 2025 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double *B, double *x) {
	double *C = (double*)calloc(N * N, sizeof(double));
    double *Ct = (double*)calloc(N * N, sizeof(double));
    double *D = (double*)calloc(N * N, sizeof(double));
    double *tmp = (double*)calloc(N, sizeof(double));
    double *y = (double*)calloc(N, sizeof(double));

    // C = B * Aᵗ
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                C[i * N + j] += B[i * N + k] * A[j * N + k];  // Aᵗ

    // Ct = Cᵗ
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            Ct[j * N + i] = C[i * N + j];

    // D = Ct * A
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                D[i * N + j] += Ct[i * N + k] * A[k * N + j];

    // Copiem x în tmp
    for (int i = 0; i < N; ++i)
        tmp[i] = x[i];

    // Loop: N iterații
    for (int iter = 0; iter < N; ++iter) {
        // y = Ct * x
        for (int i = 0; i < N; ++i) {
            y[i] = 0.0;
            for (int j = 0; j < N; ++j)
                y[i] += Ct[i * N + j] * tmp[j];
        }

        // x = C * y  (scriem în tmp)
        for (int i = 0; i < N; ++i) {
            tmp[i] = 0.0;
            for (int j = 0; j < N; ++j)
                tmp[i] += C[i * N + j] * y[j];
        }
    }

    // y = D * x (final result)
    for (int i = 0; i < N; ++i) {
        y[i] = 0.0;
        for (int j = 0; j < N; ++j)
            y[i] += D[i * N + j] * tmp[j];
    }

    // cleanup
    free(C);
    free(Ct);
    free(D);
    free(tmp);

    return y;
}
