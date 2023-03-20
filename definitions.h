#ifndef DEFINITIONS_H
#define DEFINITIONS_H

static const int us = 8; // x

static const int al = 3;
static const int ar = 5;
static const int ao = 6;
static const int ua[3] = {al, ar, ao}; // α - shifts

static const int gl = 2;
static const int gr = 3;
static const int go = 5;
static const int ug[3] = {gl, gr, go}; // δ - shifts

static const int uy = 6;               // γ
static const int ub = 7;               // β - shifts
static const int pl = 9;               // ρl
static const int pr = 11;              // ρr
static const int po = pl * pr;         // ρo
static const int up[3] = {pl, pr, po}; // ρl
static const int ut[3][3] = {
    {1, 1, 1},
    {al, ar, ao},
    {ub, ub, ub},
}; // ρl

static const char *const sht[3] = {"", "*α", "*β"};
static const char sub[4] = {'l', 'r', 'o', 'z'};
static const char opr[4] = {'L', 'R', 'O', 'Z'};
#define newEncrypted                                                           \
    malloc(sizeof(*results));                                                  \
    results->p[0] = results->l;                                                \
    results->p[1] = results->r;                                                \
    results->p[2] = results->o;

#define newCapitals                                                            \
    malloc(sizeof(*capitals));                                                 \
    capitals->L = 0;                                                           \
    capitals->R = 0;                                                           \
    capitals->O = 0;                                                           \
    capitals->Z = 0;                                                           \
    capitals->P[0] = &capitals->L;                                             \
    capitals->P[1] = &capitals->R;                                             \
    capitals->P[2] = &capitals->O;
#define ForLRO for (int i = 0; i < 3; i++)

#define ForVariables for (int j = 0; j < length; j++)
#define ForVariablesBackwards for (int j = length - 1; j > -1; j--)

#define ForVerifier for (int j = 0; j < verifiers; j++)
#define ForProver for (int j = verifiers; j < length; j++)

#define ForOperations for (int k = 0; k < operations; k++)
#define ForOperationsBackwards for (int k = operations - 1; k > -1; k--)
#endif // !DEFINITIONS_H
