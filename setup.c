#include "setup.h"
#include <stdio.h>
#include <stdlib.h>

void display(t_subpolynomials lro) {
    puts("Coefficients of subpolynomials for:");
    puts("Input/output variables:");
    ForVerifier {
        ForLRO {
            printf("%c%c: ", sub[i], var[j]);
            for (int k = operations - 1; k > -1; k--)
                printf("%0.1lf ", ((double ***)lro.p)[i][j][k]);
            putchar('\n');
        }
        putchar('\n');
    }
    puts("Prover:");
    ForProver {
        ForLRO {
            printf("%c%c = ", sub[i], var[j]);
            for (int k = operations - 1; k > -1; k--)
                printf("%0.1lf ", ((double ***)lro.p)[i][j][k]);
            putchar('\n');
        }
        putchar('\n');
    }
}
void display_evaluations_v(int i,
                           double evals[verifiers],
                           double **p,
                           const int powers) {
    char s[11];
    sprintf(s, powers ? "*%d*" : "*", powers);
    printf("%d%s( | ", up[i], s);
    ForVerifier {
        ForOperationsBackwards printf("%0.1lf*%d + ", p[j][k], ipow(us, k));
        printf("0 = %0.1lf | ", evals[j]);
    }
    fputs(") = ", stdout);
}

void display_evaluations_p(int i,
                           double evals[provers],
                           double **p,
                           const int powers) {
    char s[11];
    sprintf(s, powers ? "*%d*" : "*", powers);
    printf("%d%s( | ", up[i], s);
    ForProver {
        ForOperationsBackwards printf("%0.1lf*%d + ", p[j][k], ipow(us, k));
        printf("0 = %0.1lf | ", evals[j]);
    }
    fputs(") = ", stdout);
}

encrypted *Verifiers(t_subpolynomials lro) {
    encrypted *results = newEncrypted;
    /**
     * compute subpolynomials lro
     */
    putchar('\n');
    ForLRO {
        double evals[length];
        ForVerifier {
            evals[j] = poly_eval(((double **)lro.p[i])[j], operations, us);
        }
        printf("ρ%c*%c(s) = ", sub[i], sub[i]);
        display_evaluations_v(i, evals, (double **)lro.p[i], 0);
        ForVerifier {
            double result =
                up[i] * poly_eval(((double **)lro.p[i])[j], operations, us);
            results->p[i][j] = result;
            printf("%0.1lf ", results->p[i][j]);
        }
        putchar('\n');
    }

    return results;
}

/**
 * compute lroz
 */
encrypted *evaluate(t_subpolynomials lro, const int *powers) {
    encrypted *results = newEncrypted;
    /**
     * compute subpolynomials lro
     */
    putchar('\n');
    ForLRO {
        double evals[length];
        ForProver {
            evals[j] = gsl_poly_eval(((double **)lro.p[i])[j], operations, us);
        }
        printf("ρ%c%s*%c(s) = ", sub[i], (powers ? "*α" : ""), sub[i]);
        display_evaluations_p(i, evals, (double **)lro.p[i],
                              powers ? powers[i] : 0);

        ForProver {
            double result = up[i] * evals[j] * (powers ? powers[i] : 1);
            results->p[i][j] = result;
            printf("%0.1lf ", results->p[i][j]);
        }
        putchar('\n');
    }
    /**
     * compute subpolynomials z
     * as we have already multiplied lro by ρlro
     * we don't need to do it again
     */
    if (!powers) {
        printf("%c(s) = ", sub[3]);
        ForProver printf("| %d*(%0.1lf+%0.1lf+%0.1lf) ", ub, results->l[j],
                         results->r[j], results->o[j]);
        fputs("| = ", stdout);
        ForProver {
            results->z[j] =
                ub * (results->l[j] + results->r[j] + results->o[j]);
            printf("%0.1lf ", results->z[j]);
        }
        putchar('\n');
    }

    return results;
}
void display_t(const int *powers, int *T[3], int Tx) {

    printf("t(%d)= ", us);
    for (int k = operations; k > -1; k--)
        printf("%0.1lf*%d + ", t[k], powers[k]);
    printf("0 = %d\n", Tx);
    for (int j = 0; j < 3; j++)
        ForLRO {
            printf("ρ%c%s*t = %d * %d * %d = %d\n", sub[i], sht[j], ut[j][i],
                   up[i], Tx, T[j][i]);
        }
}
int *X() {
    static int powers[length];
    ForVariables powers[j] = ipow(us, j);
    return powers;
}

/* setup phase of the protocol To work with all values are provided raw by the
 * setup, as is L by the prover. This breaks the security guarantees and should
 * only be used for example computations
 */
t_setup setup() {
    const int *powers = X();
    const t_subpolynomials lro = polynomials();
    display(lro);

    printf("Evaluations of verifier's subpolynomials at s = %d:", us);
    encrypted *subpolynomials_v = Verifiers(lro);

    printf("Evaluations of prover's subpolynomials at s = %d:", us);
    encrypted *subpolynomials_p = evaluate(lro, NULL);

    printf("Shifted subpolynomial evaluations at x = %d, α=%d,%d,%d:", us,
           ua[0], ua[1], ua[2]);
    encrypted *shifts = evaluate(lro, ua);

    int **T = malloc(sizeof(int *) * 3);
    const int Tx = tx(us);
    for (int j = 0; j < 3; j++) {
        T[j] = malloc(sizeof(int) * 3);
        ForLRO { T[j][i] = ut[j][i] * up[i] * Tx; }
    }
    display_t(powers, T, Tx);
    static const int beta = ub * uy;

    putchar('\n');
    const t_setup keys = {
        {powers, .subpolynomials = subpolynomials_p, shifts, .t = T, lro},
        {subpolynomials_v, T[0][2], beta}};
    return keys;
}
