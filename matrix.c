/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <snb@FreeBSD.org> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. -Nick Barkas
 * ----------------------------------------------------------------------------
 */

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"
#include "matrix.h"
#include "timing.h"

void 
matrix_eig(real_t *a, real_t *wr, real_t *wi, real_t *vr, lpint n)
{
	struct timing_info start, end;
	real_t *vl, *work;
	real_t worksize;
	lpint lwork, info;
	char jobvl, jobvr;

	/* We want the right eigenvectors, but don't care about the left. */
	jobvl = 'N';
	jobvr = 'V';

	/* 
	 * vl is the left eigenvectors, which are not calculated so don't need
	 * memory allocated.
	 */
	vl = NULL;

	/* 
	 * geev will calculate the optimal size of work, a temporary array
	 * needed by geev, if we set lwork to -1. This size is saved in the 12th
	 * argument, where normally the work array itself would be. So, get the
	 * optimal work size and then allocate an appropriate amount of memory.
	 */
	lwork = -1;
	geev(&jobvl, &jobvr, &n, a, &n, wr, wi, vl, &n, vr, &n, &worksize, 
	    &lwork, &info);
	/* info should be non-zero only if geev had problems. */
	assert((int) info == 0);
	lwork = (lpint) worksize;
	work = malloc(sizeof(real_t) * lwork);
	assert(work != NULL);

	/* Now calculate eigenvalues and eigenvectors. */
	start = timing_now();
	geev(&jobvl, &jobvr, &n, a, &n, wr, wi, vl, &n, vr, &n, work, &lwork, 
	    &info);
	end = timing_now();
	timing_print_elapsed(start, end);
	assert((int) info == 0);

	/* Free up temporary memory. */
	free(work);
}

/* 
 * Multiply matrix a by b, saving the result in c, using the appropriate level 3
 * BLAS function. Matrices are n x n and should be stored in column major
 * order. 
 */
 // XXX: handle non-square matrices
void
matrix_mult(real_t *a, real_t *b, real_t *c, int n)
{
	struct timing_info start, end;
	
	/*
	 * We don't need to transpose or conjugate our matrices prior to 
	 * multiplying, nor will we multiply them by a scalar or add a constant 
	 * matrix.
	 */
	start = timing_now();
	gemm(CblasColMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, a, n, b, 
	    n, 0.0, c, n);
	end = timing_now();
	timing_print_elapsed(start, end);
}

void
matrix_random(real_t *a, int n)
{
	unsigned int i;

	/* PRNG is seeded with number of seconds since epoch. */
	srandom((int) time(NULL));
	
	for (i = 0; i < n; i++)
		a[i] = ((real_t) random()) / RAND_MAX;
}

/* 
 * Test matrix multiplication and eigenvalue computing functions with some
 * constant small, manageable matrices. We compare results to some computed with
 * Matlab to make sure we get accurate answers. 
 */
 // XXX: test multiplication of non-square matrices
void
matrix_test()
{
	int i;
	real_t c[25];
	real_t eval_re[5];
	real_t eval_im[5];
	real_t evec[25];
	
	/* a and b are our test matrices */
	real_t a[] = { -3.4, 2.9, -1.9, 0.3, -3.3, 1.0, -2.4, 1.5, 1.9, 2.5,
	    -0.5, -4.2, -2.7, 4.1, -3.5, 3.3, 0.4, 5.0, -4.2, -0.6, -3.9,
	    4.6, -5.0, 2.7, 3.2 };
	
	real_t b[] = { 3.7, -4.2, -1.0, -2.4, 3.0, -0.7, 4.1, -3.2, -2.4, -3.5, 
	    -3.6, 3.7, 0.8, 0.5, -3.6, 3.5, 1.2, -1.5, 0.1, -1.0, -4.2, -2.6, 
	    -3.8, -3.2, -2.6 };
	
	/* c is the result of multiplying a*b, computed with Matlab */
	real_t c_known[] = { -35.9, 37.85, -37.63, 7.21, -8.17, 13.81, -15.49, 
	    21.62, -4.91, 14.0, 31.23, -39.04, 30.73, -2.59, 6.51, -5.72, 9.01, 
	    4.7, -5.94, -6.56, 13.16, -3.22, 11.34, -15.36, 14.26 };
	
	/* Eigenvalues of a calculated with Matlab. They're all real */
	real_t eval_known[] = { -10.2797, 6.2545, -4.8991, -1.6353, 1.0596 };

	/* 
	 * Test matrix multiplication, making sure we match the known results 
	 * to at least 5 digits 
	 */
	matrix_mult(a, b, c, 5);
	for (i = 0; i < 25; i++)
		assert(fabs((double) (c[i] - c_known[i])) < 1e-5);

	/* 
	 * Then test eigenvalue computation, making sure we match the known 
	 * results to at least 3 digits 
	 */
	matrix_eig(a, eval_re, eval_im, evec, 5);
	for (i = 0; i < 5; i++) {
		assert(fabs((double) (eval_re[i] - eval_known[i])) < 1e-3);
		assert(fabs((double) eval_im[i]) < 1e-3);
	}
}
