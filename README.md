This is labench, an oh-so-catchy name for linear algebra benchmarking. To build
the tests, just run make, or gmake on systems where the make command is not GNU
make. You will probably have to modify the Makefile to choose which libraries
you want to test. After compiling, you will end up with a number of binaries for
testing double and single precision versions of the test routines using each of
the library versions specified in the Makefile. So far I have tested labench
only on Mac OS X 10.6 and Ubuntu Linux 9.04. It might work on other systems, but
no promises.

This project was started because I was interested in comparing the performance
of different implementations of common linear algebra libraries such as
[BLAS](http://www.netlib.org/blas) and [LAPACK](http://www.netlib.org/lapack).
Right now it is possible to measure the CPU and wall clock time of multiplying
dense general matrices together with the sgemm and dgemm routines from level 3
BLAS, and the speed of finding eigenvalues and eigenvectors of a dense general
matrix using sgeev and dgeev LAPACK routines. 

Another tool for benchmarking numerical computing performance is [HPCC, the High
Performance Computing Challenge](http://icl.cs.utk.edu/hpcc/). HPCC even
includes a dgemm test. My goal with labench was to focus specifically on making
it easy to compare performance of different implementations of the same
libraries, so one can decide which library is the best choice to use on a given
machine. I also hope to make it very easy to extend labench to support
performance  testing of other BLAS and LAPACK functions, and possibly also other
numerical libraries.

labench is fairly basic right now, but take a look at the TODO file to see what
sort of things are planned for its future.

-- Nick Barkas <snb@FreeBSD.org>
