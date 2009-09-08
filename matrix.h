/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <snb@FreeBSD.org> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. -Nick Barkas
 * ----------------------------------------------------------------------------
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "defs.h"

void matrix_eig(real_t *a, real_t *wr, real_t *wi, real_t *vr, lpint n);
void matrix_mult(real_t *a, real_t *b, real_t *c, int n);
void matrix_random(real_t *a, int n);
void matrix_test();

#endif
