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
	int n;
	real_t *a;
	real_t *b;
	real_t *c;
	real_t *wr;
	real_t *wi;
	struct timing_info start, end;

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
	start = timing_now();
	matrix_mult(a, b, c, n);
	end = timing_now();
	timing_print_elapsed(start, end);

	/* 
	 * And then calculate eigenvectors and eigenvalues of the product.
	 * Eigenvectors will just be stored in a since we don't care about it. 
	 */
	start = timing_now();
	matrix_eig(c, wr, wi, a, (lpint) n);
	end = timing_now();
	timing_print_elapsed(start, end);

	/* Free memory */
	free(a);
	free(b);
	free(c);
	free(wr);
	free(wi);
	
	return 0;
}
