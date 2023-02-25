#include <ncurses.h>

#ifndef __GLOBAL_H__
	#define __GLOBAL_H__
	#define CLOCKS_TO_SEC(clocksGivenAsInput) ((double) (clocksGivenAsInput) / CLOCKS_PER_SEC)

	typedef struct Point {
		int16_t y;
		int16_t x;
	} Point;

#endif //__GLOBAL_H__
