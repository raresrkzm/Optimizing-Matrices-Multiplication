/*
 * Tema 3 ASC
 * 2025 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double *B, double *x) {
    double *At  = (double *) calloc(N * N, sizeof(double));
    double *Ct  = (double *) calloc(N * N, sizeof(double));
    double *C   = (double *) calloc(N * N, sizeof(double));
    double *D   = (double *) calloc(N * N, sizeof(double));
    double *tmp = (double *) calloc(N, sizeof(double));
    double *y   = (double *) calloc(N, sizeof(double));

    // se transpune A (cache-friendly)
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            At[j * N + i] = A[i * N + j];

    // C = B * At
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < N; ++k)
                sum += B[i * N + k] * At[k * N + j];
            C[i * N + j] = sum;
        }

    // se transpune C
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            Ct[j * N + i] = C[i * N + j];

    // D = Ct * A
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < N; ++k)
                sum += Ct[i * N + k] * A[k * N + j];
            D[i * N + j] = sum;
        }

    // se copiaza vectorul x
    for (int i = 0; i < N; ++i)
        tmp[i] = x[i];

    for (int it = 0; it < N; ++it) {
        // y = Ct * x
        for (int i = 0; i < N; ++i) {
            double sum = 0.0;
            for (int j = 0; j < N; ++j)
                sum += Ct[i * N + j] * tmp[j];
            y[i] = sum;
        }

        // x = C * y
        for (int i = 0; i < N; ++i) {
            double sum = 0.0;
            for (int j = 0; j < N; ++j)
                sum += C[i * N + j] * y[j];
            tmp[i] = sum;
        }
    }

    // y = D * x
    for (int i = 0; i < N; ++i) {
        double sum = 0.0;
        for (int j = 0; j < N; ++j)
            sum += D[i * N + j] * tmp[j];
        y[i] = sum;
    }

    free(At);
    free(C);
    free(Ct);
    free(D);
    free(tmp);

    return y;
}