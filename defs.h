#ifndef DEFS_H
#define DEFS_H

#ifdef USE_ACCELERATE
#include <Accelerate/Accelerate.h>
typedef __CLPK_integer ext_int;
#endif

#if defined(USE_GOTO) || defined(USE_REF)
#include <cblas.h>
typedef blasint ext_int;
//#include <clapack.h>
// XXX fixme
extern void sgeev_(const char *, const char *, ext_int *, float *, ext_int *, float *, float *,float *, ext_int *, float *, ext_int *, float *, ext_int *, ext_int *);
extern void dgeev_(const char *, const char *, ext_int *, double *, ext_int *, double *, double *,double *, ext_int *, double *, ext_int *, double *, ext_int *, ext_int *);
#endif

#ifdef USE_MKL
#include <mkl.h>
typedef MKL_INT ext_int;
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
