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

#ifdef USE_ACCELERATE
#include <Accelerate/Accelerate.h>
/* 
 * LAPACK functions from different libraries all seem to have their own way of 
 * defining what an integer is. This is the type with the Accelerate framework
 */
typedef __CLPK_integer lpint;
#endif

#if defined(USE_GOTO)
#include <goto/cblas.h>
#include <goto/f2c.h>
#include <goto/clapack.h>
/* With this LAPACK, an integer is the integer type defined in f2c.h */
typedef integer lpint;
#endif

#ifdef USE_MKL
#include <mkl.h>
/* And MKL too has its own int type for LAPACK. */
typedef MKL_INT lpint;
#endif

/* 
 * We need different BLAS and LAPACK functions depending on whether we are using
 * single or double precision numbers 
 */
#ifdef USE_SINGLE
#define gemm cblas_sgemm
#define geev sgeev_
#elif USE_DOUBLE
#define gemm cblas_dgemm
#define geev dgeev_
#endif

void matrix_eig(real_t *a, real_t *wr, real_t *wi, real_t *vr, lpint n);
void matrix_mult(real_t *a, real_t *b, real_t *c, int n);
void matrix_random(real_t *a, int n);
void matrix_test();

#endif
