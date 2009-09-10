/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <snb@FreeBSD.org> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. -Nick Barkas
 * ----------------------------------------------------------------------------
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "defs.h"
#include "matrix.h"
#include "timing.h"

/* 
 * We shall test the level 3 BLAS gemm routine and LAPACK's geev routine by
 * multiplying two random matrices together then finding the eigenvalues and
 * eigenvectors of the product. We'll measure both wall clock and CPU time used
 * by each of these operations 
 */
int
main(int argc, char **argv)
{
	struct timing_duration elapsed;
	real_t *a, *b, *c, *wr, *wi;
	int n;

	/* Get size of matrix n as command line argument */
	assert(argc == 2);
	n = strtol(argv[1], NULL, 10);
	
	/* 
	 * First we do some tests with small matrices to make sure our
	 * multiplication and eigenvalue calculations are working correctly 
	 */
	matrix_test();
	
	/* Allocate memory and generate random values to fill a and b */
	a = (real_t *) malloc(sizeof(real_t) * n * n);
	b = (real_t *) malloc(sizeof(real_t) * n * n);
	c = (real_t *) malloc(sizeof(real_t) * n * n);
	wr = (real_t *) malloc(sizeof(real_t) * n);
	wi = (real_t *) malloc(sizeof(real_t) * n);
	assert(a != NULL && b != NULL && c != NULL);
	matrix_random(a, n*n);
	matrix_random(b, n*n);
	
	/* Now do the matrix multiplication test */
	elapsed = matrix_mult(a, b, c, n);
	printf("Multiplication CPU time: %.3f wall time: %.3f\n", elapsed.cpu,
	    elapsed.wall);

	/* 
	 * And then calculate eigenvectors and eigenvalues of the product.
	 * Eigenvectors will just be stored in a since we don't care about it. 
	 */
	elapsed = matrix_eig(c, wr, wi, a, (lpint) n);
	printf("Eigenvalue/vector CPU time: %.3f wall time: %.3f\n", 
	    elapsed.cpu, elapsed.wall);

	/* Free memory */
	free(a);
	free(b);
	free(c);
	free(wr);
	free(wi);
	
	return 0;
}
