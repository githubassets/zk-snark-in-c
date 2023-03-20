#ifndef STRUCTS_H
#define STRUCTS_H
#include "definitions.h"
#include "initial.h"

typedef struct s_bigger {
    double L[operations];
    double R[operations];
    double O[operations];
    const void *P[3];
} t_bigger;

// stores evaluations of subpolynomials at s
typedef struct s_encrypted {
    double l[length];
    double r[length];
    double o[length];
    double z[length];
    double *p[3];
} encrypted;

// Stores operand polynomials
typedef struct s_capitals {
    double L;
    double R;
    double O;
    double Z; // optional
    double *P[3];
} t_capitals;

// stores all subpolynomials
typedef struct s_subpolynomials {
    double l[length][operations];
    double r[length][operations];
    double o[length][operations];
    void *p[3];
} t_subpolynomials;

// stores proving keys
typedef struct s_proving {
    const int *powers[length];
    encrypted *subpolynomials;
    encrypted *shifted;
    int **t;
    const t_subpolynomials lro;
} proving;

// stores verification keys
typedef struct s_verification {
    encrypted *subpolynomials_v;
    int to;
    const int beta;
} verification;

// stores proving and verification keys
typedef struct s_setup {
    const proving Proving;
    const verification Verification;
} t_setup;

// the proof
typedef struct s_proof {
    t_capitals *regular;
    t_capitals *shifted;
    double h;
} t_proof;

static const struct s_evaluations {
    const double l[length][operations];
    const double r[length][operations];
    const double o[length][operations];
    const void *p[3];
}
/** coefficients of each variable at each computation, variables not used in an
   operand not included*/
evaluations = EVALUATIONS
#endif // !STRUCTS_H
