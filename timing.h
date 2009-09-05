#ifndef TIMING_H
#define TIMING_H

#include <stdint.h>
#include <time.h>

/* 
 * This is meant to store CPU time since the process started and current wall
 * clock time from a monotonic clock. 
 */
struct timing_info {
	clock_t cpu;
#ifdef __APPLE__
	uint64_t wall;
#else
	struct timespec wall;
#endif
};

inline struct timing_info timing_now();
void timing_print_elapsed(struct timing_info start, struct timing_info end);

#endif
