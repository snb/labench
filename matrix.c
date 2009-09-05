#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"

void 
matrix_eig(real_t *a, real_t *wr, real_t *wi, real_t *vr, ext_int n)
{
	/* We want the right eigenvectors, but don't care about the left */
	char jobvl = 'N';
	char jobvr = 'V';

	/* 
	 * vl is the left eigenvectors, which are not calculated so don't need
	 * memory allocated 
	 */
	real_t *vl = NULL;

	/* 
	 * work is some temporary work space needed by geev, and lwork is its
	 * size.  geev will calculate the optimal size for work for us if we set
	 * lwork to -1, then we'll use that value for allocating work's memory 
	 */
	real_t *work;
	real_t worksize;
	ext_int lwork = -1;

	/* 
	 * Diagnostic info about any problems geev encounters. Should be zero 
	 * after a successful run 
	 */
	ext_int info;

	/* 
	 * Calculate the optimal size of work then allocate an appropriate 
	 * amount of memory 
	 */
	geev(&jobvl, &jobvr, &n, a, &n, wr, wi, vl, &n, vr, &n, &worksize, 
	    &lwork, &info);
	assert(info == 0);
	lwork = (ext_int) worksize;
	work = (real_t *) malloc(sizeof(real_t) * lwork);
	assert(work != NULL);

	/* Now calculate eigenvalues and eigenvectors */
	geev(&jobvl, &jobvr, &n, a, &n, wr, wi, vl, &n, vr, &n, work, &lwork, 
	    &info);
	assert(info == 0);

	/* Free up temporary memory */
	free(work);
}

/* 
 * Multiply matrix a by b, saving the result in c, using the appropriate level 3
 * BLAS function. Matrices are n x n and should be stored in column major
 * order. 
 */
 // XXX: handle non-square matrices
void
matrix_mult(real_t *a, real_t *b, real_t *c, ext_int n)
{
	/*
	 * We don't need to transpose or conjugate our matrices prior to 
	 * multiplying, nor will we multiply them by a scalar or add a constant 
	 * matrix 
	 */
	char trans = 'n';
	real_t alpha = 1.0;
	real_t beta = 0.0;
	
	gemm(&trans, &trans, &n, &n, &n, &alpha, a, &n, b, &n, &beta, c, &n);
}

void
matrix_random(real_t *a, ext_int n)
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
