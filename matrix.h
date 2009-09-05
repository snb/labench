#ifndef MATRIX_H
#define MATRIX_H

#include "defs.h"

void matrix_eig(real_t *a, real_t *wr, real_t *wi, real_t *vr, ext_int n);
void matrix_mult(real_t *a, real_t *b, real_t *c, ext_int n);
void matrix_random(real_t *a, ext_int n);
void matrix_test();

#endif
