/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <snb@FreeBSD.org> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. -Nick Barkas
 * ----------------------------------------------------------------------------
 */

#ifndef TIMING_H
#define TIMING_H

#include <stdint.h>
#include <time.h>

/*
 * This is meant to store CPU time since the process started and current wall
 * clock time from a monotonic clock.
 */
struct timing_clock {
	clock_t cpu;
#ifdef __APPLE__
	uint64_t wall;
#else
	struct timespec wall;
#endif
};

/*
 * Store elapsed wall and CPU time in seconds, as doubles.
 * XXX: We do not actually know how accurate these times are, because the
 * resolution of the clocks varies by system.
 */
struct timing_duration {
	double cpu;
	double wall;
};

inline struct timing_clock timing_now();
struct timing_duration timing_compute_duration(struct timing_clock start,
    struct timing_clock end);

#endif
