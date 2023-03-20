#include "verifier.h"
bool same(double a, double b) { return fabs(a - b) < a / 10; }

void display_resulting(encrypted evaluations, t_capitals regular) {
    t_capitals *capitals = newCapitals;
    ForLRO {
        printf("%c(s) = %cv(s) + %cp(s) = ", opr[i], opr[i], opr[i]);
        ForVerifier {
            printf("%0.1lf*%d + ", evaluations.p[i][j], values[j]);
            *capitals->P[i] += evaluations.p[i][j] * values[j];
        }
        *capitals->P[i] += *regular.P[i];
        printf("%0.1lf = %0.1lf\n", *regular.P[i], *capitals->P[i]);
    }
}
void display_right(double h, double t, double O, double right) {
    printf("E(th+O) = E(%0.1lf*%0.1lf+%0.1lf) = E(%0.1lf)\n ", t, h, O, right);
}

t_capitals *resulting(encrypted evaluations, t_capitals regular) {
    t_capitals *capitals = newCapitals;
    ForLRO {
        ForVerifier { *capitals->P[i] += evaluations.p[i][j] * values[j]; }
        *capitals->P[i] += *regular.P[i];
    }

    return capitals;
}

short beta(t_capitals *capitals, const int beta) {
    printf("βγ*(L(s)+R(s)+O(s)) = %d*(%0.1lf+%0.1lf+%0.1lf) = %0.1lf\n", beta,
           capitals->L, capitals->R, capitals->O,
           capitals->L * beta + capitals->R * beta + capitals->O * beta);
    printf("Z(s)*γ = %0.1lf*%d = %0.1lf\n", capitals->Z, uy, capitals->Z * uy);

    return same(capitals->Z * uy,
                capitals->L * beta + capitals->R * beta + capitals->O * beta);
}

bool verifier(t_proof proof, verification keys) {

    ForLRO { //
        printf("%c*%d = %c`\n", opr[i], ua[i], opr[i]);
    }
    const short respected =
        (same(proof.regular->L * ua[0], proof.shifted->L)) &&
        (same(proof.regular->R * ua[1], proof.shifted->R)) &&
        (same(proof.regular->O * ua[2], proof.shifted->O));

    if (respected) puts("All shifts respected\n");
    else puts("Shift comparison not passed\n");

    const short checksum = beta(proof.regular, keys.beta);
    if (checksum) puts("Variable consistency passed\n");
    else puts("Variable consistency not passed\n");
    const t_capitals *LROv = resulting(*keys.subpolynomials_v, *proof.regular);
    const double left = LROv->R * LROv->L;
    display_resulting(*keys.subpolynomials_v, *proof.regular);
    printf("E(ρl*L*ρr*R)=E(%0.2lf)\n\n", left);

    printf("E(h) = E(%0.1lf)\n", proof.h);
    const double right = proof.h * keys.to + LROv->O;
    display_right(proof.h, keys.to, LROv->O, right);
    const short evaluated = same(right, left);
    if (evaluated) puts("\nE(ρlρr*LR) == E(ρlρr*th+ρlρr*O)\n");
    else puts("Evaluation polynomials don't match\n");

    free(proof.regular);
    free(proof.shifted);
    return respected && evaluated && checksum;
}
