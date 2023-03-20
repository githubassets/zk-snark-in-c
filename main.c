#include "definitions.h"
#include "prover.h"
#include "setup.h"
#include "structs.h"
#include "verifier.h"
#include <gmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

// the entire algorithm
int zksnark() {
    printf("s=%d, αlro=%d,%d,%d, β=%d, γ=%d, ρl=%d, ρr=%d, "
           "ρo=%d\n",
           us, ua[0], ua[1], ua[2], ub, uy, pl, pr, po);
    // Setup
    puts("-------Setup-------");
    const t_setup keys = setup();
    // Prover
    puts("------Proving-------");
    const t_proof proof = prover(keys.Proving);
    // Verifier
    puts("----Verification----");
    const bool result = verifier(proof, keys.Verification);
    if (result) puts("Verified successfully");
    else puts("false proof");

    ForLRO ForVariables free(((double **)keys.Proving.lro.p[i])[j]);

    return result;
}

int main(void) {
    zksnark();
    return 0;
}
