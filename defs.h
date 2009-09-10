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

/* 
 * Define real_t as a single or double precision floating point number,
 * depending on whether USE_SINGLE or USE_DOUBLE is defined 
 */
#ifdef USE_SINGLE
typedef float real_t;
#elif USE_DOUBLE
typedef double real_t;
#endif

#endif
