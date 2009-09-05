#include <stdio.h>
#include <time.h>

#ifdef __APPLE__
#include <mach/mach_time.h>
#endif

#include "timing.h"

/* 
 * Monotonic timing stuff for Mac OS X was helped greatly by 
 * http://www.wand.net.nz/~smr26/wordpress/2009/01/19/monotonic-time-in-mac-os-x
 */

/* 
 * Get current wall time with a monotonic clock and CPU time since the program 
 * started 
 */
inline struct timing_info
timing_now()
{
	struct timing_info info;

	info.cpu = clock();
#ifdef __APPLE__
	info.wall = mach_absolute_time();
#else
	clock_gettime(CLOCK_MONOTONIC, &info.wall);
#endif

	return info;
}

/* 
 * Print out the elapsed CPU and wall time between two timing_info structs, in
 * seconds 
 */
void 
timing_print_elapsed(struct timing_info start, struct timing_info end)
{
	double wall_elapsed;
	double cpu_elapsed = (double) (end.cpu - start.cpu) / CLOCKS_PER_SEC;

#ifdef __APPLE__
	mach_timebase_info_data_t info;
	mach_timebase_info(&info);
	wall_elapsed = 1e-9 * (end.wall - start.wall) * info.numer / info.denom;
#else
	wall_elapsed = end.wall.tv_sec - start.wall.tv_sec + 1e-9 * 
	    (end.wall.tv_nsec - start.wall.tv_nsec);
#endif
	/* 
	 * XXX: We don't actually know how accurate these timers are; it varies 
	 * by system. It should be safe to say we have at least three digits of
	 * accuracy, though. 
	 */
	printf("CPU time: %.3f wall time: %.3f\n", cpu_elapsed, wall_elapsed);
}
