#include "prover.h"
#include <stdio.h>

double *multiply(const double A[], const double B[], int m, int n) {
    double *prod = malloc(sizeof(double) * (m + n - 1));
    for (int i = 0; i < m + n - 1; i++)
        prod[i] = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            prod[i + j] += A[i] * B[j];

    return prod;
}

double *divide(const double *dividend,
               const double divisor[operations + 1],
               const int m,
               const int n) {
    double *quotient = malloc(sizeof(double) * operations * 2 + length);
    for (int i = 0; i < m; i++)
        quotient[i] = dividend[i];

    double normalizer = divisor[0];

    for (int i = 0; i < m - (n - 1); i++) {
        quotient[i] /= normalizer;
        double coef = quotient[i];
        if (coef != 0)
            for (int j = 1; j < n; j++)
                quotient[i + j] += -divisor[j] * coef;
    }

    return quotient;
}
void concat(double **variable,
            const int coefficients[length],
            double *operand) {
    ForVariables ForOperations {
        operand[k] += variable[j][k] * coefficients[j];
    }
}
void display_polynomials(t_subpolynomials lro, t_bigger bigger) {
    puts("Assign all values to the unencrypted variable polynomials:");
    ForLRO {
        double operand[operations];
        printf("%c(x): ", opr[i]);
        ForOperationsBackwards {
            ForVariables {
                printf("%0.1lf*%d + ", ((double **)lro.p[i])[j][k], values[j]);
                operand[k] += ((double **)lro.p[i])[j][k] * values[j];
            }
            fputs("0 | ", stdout);
        }
        ForOperationsBackwards printf("%0.1lf ", ((double **)bigger.P)[i][k]);
        putchar('\n');
    }
}
void display_p(double *p) {
    fputs("\np(x) = L*R-O = ", stdout);
    for (int k = (operations - 1) * 2; k > -1; k--)
        printf("%0.1lf ", p[k]);
}
void zk_h(double *division, t_bigger bigger) {

    // for (int k = operations - 2; k > -1; k--)
    //     printf("%0.1lf ", division[k]);
    ForOperationsBackwards { division[k] += gr * bigger.L[k]; }
    ForOperationsBackwards { division[k] += gl * bigger.R[k]; }
    for (int k = operations; k > -1; k--) {
        division[k] += gl * gr * t[k];
    }
    division[0] -= go;
}
void display_h(const double *division, t_bigger bigger) {

    fputs("\nh(x) = (LR-O)/t + δr*L + δl*R + δlδr*t - δo = \n                  "
          "                  ",
          stdout);
    for (int k = operations - 2; k > -1; k--)
        printf("%0.1lf ", division[k]);
    fputs("+ \n                 ", stdout);
    ForOperationsBackwards {
        printf("%d*%0.1lf=%0.1lf ", gr, bigger.L[k], gr * bigger.L[k]);
    }
    fputs("+ \n                  ", stdout);
    ForOperationsBackwards {
        printf("%d*%0.1lf=%0.1lf ", gl, bigger.R[k], gl * bigger.R[k]);
    }
    fputs("+ \n", stdout);
    for (int k = operations; k > -1; k--) {
        printf("%d*%d*%0.1lf=%0.1lf ", gl, gr, t[k], gl * gr * t[k]);
    }
    printf("-\n                                      %d = \n", go);
}
void dispay_resulting_h(const double *h) {
    for (int j = operations; j > -1; j--)
        printf("%0.1lf + ", h[j]);
    putchar('0');
}

const double *polytemp(t_subpolynomials lro) {
    const t_bigger bigger = {.P = {&bigger.L, &bigger.R, &bigger.O}};

    ForLRO concat(lro.p[i], values, (double *)bigger.P[i]);
    display_polynomials(lro, bigger);

    double *p = multiply(bigger.L, bigger.R, operations, operations);
    for (int k = operations - 1; k > -1; k--)
        p[k] -= bigger.O[k];
    display_p(p);

    fputs("\nt(x) = ", stdout);
    for (int k = operations; k > -1; k--)
        printf("%0.1lf ", t[k]);

    double *division = divide(p, t, operations * 2 - 1, operations + 1);
    display_h(division, bigger);
    zk_h(division, bigger);
    dispay_resulting_h(division);

    putchar('\n');

    free(p);
    return division;
}

void display_z(t_capitals *capitals, encrypted evaluations, const int T[3]) {
    printf("t*δ%c+t*δ%c+t*δ%c+%c = (%d*%d+%d*%d+%d*%d = %d)", sub[0], sub[1],
           sub[2], opr[3], T[0], gl, T[1], gr, T[2], go,
           T[0] * gl + T[1] * gr + T[2] * go);
    ForProver { printf(" + %0.1lf*%d", evaluations.z[j], values[j]); }
    printf(" = %0.1lf\n", capitals->Z);
}
void Z(t_capitals *capitals, encrypted evaluations, const int T[3]) {
    ForVariables { capitals->Z += evaluations.z[j] * values[j]; }
    capitals->Z += T[0] * gl + T[1] * gr + T[2] * go;
}

double eval(const double *h, const int powers[length]) {
    double result = 0;
    fputs("h(s) = ", stdout);
    for (int k = operations; k > -1; k--) {
        printf("%0.1lf*%d + ", h[k], powers[k]);
        result += h[k] * powers[k];
    }
    printf("0 = %0.1lf\n", result);
    return result;
}

/* prover's computation:
 * returns L gR gO
 */
t_capitals *results(encrypted evaluations, const int T[3]) {
    t_capitals *capitals = newCapitals;
    ForLRO {
        ForVariables { *capitals->P[i] += evaluations.p[i][j] * values[j]; }
        *capitals->P[i] += T[i] * ug[i];
    }

    return capitals;
}

void display_capitals(encrypted evaluations,
                      t_capitals *majors,
                      const int T[3],
                      char *s) {
    ForLRO {
        printf("t*δ%c+%s%c(s) = ", sub[i], s, opr[i]);
        printf("(%d*%d = %d)", T[i], ug[i], T[i] * ug[i]);
        ForProver { printf(" + %0.1lf*%d", evaluations.p[i][j], values[j]); }
        printf(" = %0.1lf\n", *((double **)majors->P)[i]);
    }
}

// generating a proof
t_proof prover(const proving keys) {
    const double *h = polytemp(keys.lro); // find the polynomial h
    const double H = eval(h, *keys.powers);

    t_capitals *majors = results(*keys.subpolynomials, keys.t[0]);
    display_capitals(*keys.subpolynomials, majors, keys.t[0], "");

    Z(majors, *keys.subpolynomials, keys.t[2]);
    display_z(majors, *keys.subpolynomials, keys.t[2]);

    t_capitals *shifted = results(*keys.shifted, keys.t[1]);

    putchar('\n');
    display_capitals(*keys.shifted, shifted, keys.t[1], "α");
    putchar('\n');

    t_proof proof = {majors, shifted, H};

    free((void *)h);
    free(keys.subpolynomials);
    free(keys.shifted);

    return proof;
}
