# Some default parameters used for all the libraries
CC = gcc
CFLAGS = -O2 -Wall

OS = $(shell uname)
ifeq ($(OS), Linux)
LDFLAGS = -lm -lrt
DEFAULT_TARG = linux
else
LDFLAGS = -lm
DEFAULT_TARG = macosx
endif

# Reference implementation of BLAS from Netlib. On Debian/Ubuntu, a static
# version of this library comes with the libblas-dev package and lapack comes
# with liblapack-dev. I had to install libatlas-headers in order to get
# clapack.h and libf2c2-dev for f2c.h. Headers and libraries are respectively in
# /usr/include and /usr/lib so gcc shouldn't need -I or -L options.
# XXX: this is actually atlas on vader
REF_BLAS_FLAGS = -lblas -llapack

# Intel Math Kernel Library
MKL_FLAGS = -I/home/snb/intel/mkl/10.2.1.017/include -L/home/snb/intel/mkl/10.2.1.017/lib/em64t -lmkl_lapack -lmkl -lguide -lpthread

# Accelerate framework on Mac OS X
ACCELERATE_FLAGS = -framework Accelerate

# GotoBLAS built and optimized for this particular CPU plus the reference C
# LAPACK implementation linked with it. We assume the headers and libraries are
# in some paths the compiler searches in automatically.
GOTOBLAS_FLAGS = -lgoto -llapack_goto

SOURCES = main.c matrix.c timing.c
HEADERS = matrix.h defs.h timing.h

default: $(DEFAULT_TARG)

macosx: acc_single acc_double goto_single goto_double

linux: ref_single ref_double mkl_single mkl_double

ref_single:
	$(CC) $(CFLAGS) $(LDFLAGS) $(REF_BLAS_FLAGS) -o ref_single $(SOURCES) -DUSE_SINGLE -DUSE_REF

ref_double: $(SOURCES) $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) $(REF_BLAS_FLAGS) -o ref_double $(SOURCES) -DUSE_DOUBLE -DUSE_REF

acc_single: $(SOURCES) $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) $(ACCELERATE_FLAGS) -o acc_single $(SOURCES) -DUSE_SINGLE -DUSE_ACCELERATE

acc_double: $(SOURCES) $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) $(ACCELERATE_FLAGS) -o acc_double $(SOURCES) -DUSE_DOUBLE -DUSE_ACCELERATE

goto_single: $(SOURCES) $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) $(GOTOBLAS_FLAGS) -o goto_single $(SOURCES) -DUSE_SINGLE -DUSE_GOTO

goto_double: $(SOURCES) $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) $(GOTOBLAS_FLAGS) -o goto_double $(SOURCES) -DUSE_DOUBLE -DUSE_GOTO

mkl_single: $(SOURCES) $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) $(MKL_FLAGS) -o mkl_single $(SOURCES) -DUSE_SINGLE -DUSE_MKL

mkl_double: $(SOURCES) $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) $(MKL_FLAGS) -o mkl_double $(SOURCES) -DUSE_DOUBLE -DUSE_MKL

clean:
	rm -f ref_single ref_double acc_single acc_double goto_single goto_double mkl_single mkl_double
	rm -rf *.dSYM
