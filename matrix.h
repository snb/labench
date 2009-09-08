#ifndef MATRIX_H
#define MATRIX_H

#include "defs.h"

void matrix_eig(real_t *a, real_t *wr, real_t *wi, real_t *vr, lpint n);
void matrix_mult(real_t *a, real_t *b, real_t *c, int n);
void matrix_random(real_t *a, int n);
void matrix_test();

#endif
