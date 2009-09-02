#ifndef DEFS_H
#define DEFS_H

#ifdef USE_ACCELERATE
#include <Accelerate/Accelerate.h>
typedef __CLPK_integer ext_int;
#endif

#if defined(USE_GOTO) || defined(USE_REF)
//#include <f2c.h>
//#include <clapack.h>
typedef int ext_int;
#endif

#ifdef USE_MKL
#include <mkl.h>
typedef MKL_INT ext_int;
#endif

/* Define real_t as a single or double precision floating point number,
 * depending on whether USE_SINGLE or USE_DOUBLE is defined */
#ifdef USE_SINGLE
 typedef float real_t;
#define gemm sgemm_
#define geev sgeev_

#elif USE_DOUBLE
typedef double real_t;
#define gemm dgemm_
#define geev dgeev_
#endif

#endif
