#include "operands.h"
#include <stdio.h>

// finds a subpolynomial of a variable at operand, la, for example
double *subpolynomial(const double dy[operations]) {
    double *store = malloc(sizeof(double) * operations);
    gsl_multifit_linear_workspace *ws;
    gsl_matrix *cov, *X;
    gsl_vector *y, *c;
    double chisq;
    int i, j;

    X = gsl_matrix_alloc(operations, operations);
    y = gsl_vector_alloc(operations);
    c = gsl_vector_alloc(operations);
    cov = gsl_matrix_alloc(operations, operations);

    for (i = 0; i < operations; i++) {
        for (j = 0; j < operations; j++)
            gsl_matrix_set(X, i, j, pow(i + 1, j));
        gsl_vector_set(y, i, dy[i]);
    }

    ws = gsl_multifit_linear_alloc(operations, operations);
    gsl_multifit_linear(X, y, c, cov, &chisq, ws);

    /* store result ... */
    for (i = 0; i < operations; i++)
        store[i] = gsl_vector_get(c, i) + 10e-9;

    gsl_multifit_linear_free(ws);
    gsl_matrix_free(X);
    gsl_matrix_free(cov);
    gsl_vector_free(y);
    gsl_vector_free(c);
    return store; // coefficients in reverse
}

// Calculating one of the three operand polynomials
double **
operand(const double evaluations[length][operations], // array of evaluations
        double **polynomial, // array of subpolynomials l/r/o
        char sub) {
    ForVariables {
        polynomial[j] = subpolynomial(evaluations[j]);

        printf("%c%c: ", sub, var[j]);
        ForOperations printf("%0.0lf ", evaluations[j][k]);
        putchar('\n');
    }
    putchar('\n');

    return polynomial;
}

// Return all polynomials with their sums
t_subpolynomials polynomials() {
    puts("Evaluations of operand subpolynomials (variable coefficients at a "
         "particular computation):");
    puts("x:  1 2 3 4 5");
    static t_subpolynomials lro = {.p = {lro.l, lro.r, lro.o}};
    ForLRO operand(evaluations.p[i], (double **)lro.p[i], sub[i]);
    return lro;
}
