/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <snb@FreeBSD.org> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. -Nick Barkas
 * ----------------------------------------------------------------------------
 */

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
 * started.
 */
inline struct timing_clock
timing_now()
{
	struct timing_clock info;

	info.cpu = clock();
#ifdef __APPLE__
	info.wall = mach_absolute_time();
#else
	clock_gettime(CLOCK_MONOTONIC, &info.wall);
#endif

	return (info);
}

/*
 * Compute the differences in CPU and wall time between two timing_clock
 * structs, in seconds.
 */
struct timing_duration
timing_compute_duration(struct timing_clock start, struct timing_clock end)
{
	struct timing_duration elapsed;

	elapsed.cpu = (double) (end.cpu - start.cpu) / CLOCKS_PER_SEC;

#ifdef __APPLE__
	mach_timebase_info_data_t info;
	mach_timebase_info(&info);
	elapsed.wall = 1e-9 * (end.wall - start.wall) * info.numer / info.denom;
#else
	elapsed.wall = end.wall.tv_sec - start.wall.tv_sec + 1e-9 *
	    (end.wall.tv_nsec - start.wall.tv_nsec);
#endif
	return (elapsed);
}
