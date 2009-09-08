/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <snb@FreeBSD.org> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. -Nick Barkas
 * ----------------------------------------------------------------------------
 */

#ifndef DEFS_H
#define DEFS_H

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
 * Define real_t as a single or double precision floating point number,
 * depending on whether USE_SINGLE or USE_DOUBLE is defined 
 */
#ifdef USE_SINGLE
typedef float real_t;
#define gemm cblas_sgemm
#define geev sgeev_

#elif USE_DOUBLE
typedef double real_t;
#define gemm cblas_dgemm
#define geev dgeev_
#endif

#endif
