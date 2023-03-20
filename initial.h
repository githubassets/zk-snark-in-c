#ifndef INITIAL_H
#define INITIAL_H
#define provers length - verifiers
/*
 * length is the variable count
 * operations are the operation count
 * t is the subpolynomial
 * values are prover's knowledge
 * EVALUATIONS are the coefficients of variables at a particular computation
 */

/*
#define length 4
#define verifiers 1
#define operations 2
#define vw 1
#define va 3
#define vv 3

#define tx(x) (x - 1) * (x - 2)
static const double t[operations + 1] = {2, -3, 1};
static const char var[length] = {'1', 'v', 'a', 'w'};
static const int values[length] = {1, vv, va, vw};
#define EVALUATIONS                                                            \
    {                                                                          \
        .l = {{0, 0}, {0, 0}, {2, 0}, {0, 1}},                                 \
        .r = {{0, 0}, {0, 0}, {0, 0}, {1, 1}},                                 \
        .o = {{0, 0}, {1, 0}, {1, 0}, {0, 1}},                                 \
        .p = {&evaluations.l, &evaluations.r, &evaluations.o},                 \
    };
    */

/*v,a,w*/

/*
if w return a//
else return -a//

//w*a+(1-w)*-a=v => a*w+a*w-a=v => 2a*w = v+a

2a w v+a
w w w
*/

/*
#define length 4
#define verifiers 2
#define operations 2
#define vw 1
#define va 13
#define vv 15

#define tx(x) (x - 1) * (x - 2)
static const double t[operations + 1] = {2, -3, 1};
static const char var[length] = {'1', 'a', 'v', 'w'};
static const int values[length] = {1, va, vv, vw};
#define EVALUATIONS                                                            \
    {                                                                          \
        .l = {{0.5, 0}, {0.5, 0}, {0, 0}, {0.5, 1}},                           \
        .r = {{2, 0}, {0, 0}, {0, 0}, {0, 1}},                                 \
        .o = {{0, 0}, {0, 0}, {1, 0}, {0, 1}},                                 \
        .p = {&evaluations.l, &evaluations.r, &evaluations.o},                 \
    };
    */

/*1,v,a,w*/

/*
if w return a+2//
else return a+1//

wa+2w+(1-w)*(a+1)=v => wa+2w+a+1-wa-w=v => w+a+1 = v

0.5w+0.5a+0.5 2 v
w w w

l: 0.5w+0.5a+0.5 w
r: 2             w
o: v             w
*/

/*
proof a is a 4-bit number
2a 0.5 8b3+4b2+2b1+b0
b3 b3 b3
b2 b2 b2
b1 b1 b1
b0 b0 b0
*/
/*
#define length 6
#define verifiers 1
#define operations 5
#define va 15
#define vb3 1
#define vb2 1
#define vb1 1
#define vb0 1

#define tx(x) (x - 1) * (x - 2) * (x - 3) * (x - 4) * (x - 5)
static const double t[operations + 1] = {-120, 274, -225, 85, -15, 1};
static const char var[length] = {'1', 'a', '3', '2', '1', '0'};
static const int values[length] = {1, va, vb3, vb2, vb1, vb0};
#define EVALUATIONS                                                            \
    {.l = {{0, 0, 0, 0, 0},                                               \
           {0.5, 0, 0, 0, 0},                                             \
           {0, 1, 0, 0, 0},                                               \
           {0, 0, 1, 0, 0},                                               \
           {0, 0, 0, 1, 0},                                               \
           {0, 0, 0, 0, 1}},                                              \
     .r = {{2, 0, 0, 0, 0},                                               \
           {0, 0, 0, 0, 0},                                               \
           {0, 1, 0, 0, 0},                                               \
           {0, 0, 1, 0, 0},                                               \
           {0, 0, 0, 1, 0},                                               \
           {0, 0, 0, 0, 1}},                                              \
     .o = {{0, 0, 0, 0, 0},                                               \
           {0, 0, 0, 0, 0},                                               \
           {8, 1, 0, 0, 0},                                               \
           {4, 0, 1, 0, 0},                                               \
           {2, 0, 0, 1, 0},                                               \
           {1, 0, 0, 0, 1}},                                              \
     .p = {&evaluations.l, &evaluations.r, &evaluations.o}};
*/

/*
#define length 6
#define verifiers 1
#define operations 3
#define vw 1
#define vm 1
#define va 2
#define vb 2
#define vv 2

#define tx(x) (x - 1) * (x - 2) * (x - 3)
static const double t[operations + 1] = {-6, 11, -6, 1};
static const char var[length] = {'1', 'a', 'b', 'w', 'm', 'v'};
static const int values[length] = {1, va, vb, vw, vm, vv};
#define EVALUATIONS                                                            \
    {                                                                          \
        //   1          a          b          w          m          v          \
        {{0, 0, 0}, {0, 0.5, 0}, {1, 0, 0}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}},  \
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 2, 1}, {0, 0, 0}, {0, 0, 0}},    \
        {{0, 0, 0}, {0, 0, 0}, {0, -1, 0}, {0, 0, 1}, {1, 1, 0}, {0, 1, 0}},   \
        {&evaluations.l, &evaluations.r, &evaluations.o},                      \
    };
*/

/*1,v,a,w*/

/*
if w return a
else return b

w*a+(1-w)b=v => aw=v+bw-b

b w m
0.5a 2w v+m-b
w w w
*/

/*
#define length 6
#define operations 3
#define verifiers 1
#define vv 48
#define va 2
#define vw 0
#define vb 2
#define vm 48

#define tx(x) (x - 1) * (x - 2) * (x - 3)
static const double t[operations + 1] = {-6, 11, -6, 1};
static const char var[length] = {'1', 'v', 'a', 'w', 'b', 'm'};
static const int values[length] = {1, vv, va, vw, vb, vm};
#define EVALUATIONS                                                            \
    {                                                                          \
        .l = {{0, 0, 0},                                                       \
              {0, 0, 0},                                                       \
              {3, 0, 0},                                                       \
              {0, 1, 1},                                                       \
              {0, 0, 0},                                                       \
              {0, 0, 0}},                                                      \
        .r = {{0, 0, 0},                                                       \
              {0, 0, 0},                                                       \
              {0, -2, 0},                                                      \
              {0, 0, 1},                                                       \
              {4, 1, 0},                                                       \
              {0, -1, 0}},                                                     \
        .o = {{0, 0, 0},                                                       \
              {0, 1, 0},                                                       \
              {0, 0, 0},                                                       \
              {0, 0, 1},                                                       \
              {0, 0, 0},                                                       \
              {1, -1, 0}},                                                     \
        .p = {&evaluations.l, &evaluations.r, &evaluations.o},                 \
    };
    */

/*v,a,w,b,m*/

/*
if w return -2a+b
else return 3a*4b

3a 4b m
w -2a+b-m v-m
w w w

L=a*la3+w*lw
R = b*rb4 + a*ra2 + m*rm + w*rw
O = v*ov + m*om + w*ow
*/

#define length 6
#define operations 3
#define verifiers 1
#define va 4
#define vb 2
#define vw 1
#define vm 8
#define vv 8

#define tx(x) (x - 1) * (x - 2) * (x - 3)
static const double t[operations + 1] = {-6, 11, -6, 1};
static const char var[length] = {'1', 'v', 'a', 'w', 'b', 'm'};
static const int values[length] = {1, vv, va, vw, vb, vm};
#define EVALUATIONS                                                            \
    {                                                                          \
        {{0, 0, 0}, {0, 0, 0}, {1, 0, 0}, {0, 1, 1}, {0, 0, 0}, {0, 0, 0}},    \
        {{0, 0, 0}, {0, 0, 0}, {0, -1, 0}, {0, 0, 1}, {1, -1, 0}, {0, 1, 0}},  \
        {{0, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, -1, 0}, {1, 0, 0}},  \
        {&evaluations.l, &evaluations.r, &evaluations.o},                      \
    };

/*v,a,w,b,m*/
/*
if w return a*b
else return a+b

a b m
w m-a-b v-a-b
w w w
*/

#endif // INITIAL_H
