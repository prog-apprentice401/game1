#include <ncurses.h>
#include "global.h"

#ifndef __WINDOW_H__
	#define __WINDOW_H__

	typedef struct Border {
		attr_t top;
		attr_t bottom;
		attr_t right;
		attr_t left;
		attr_t topLeft;
		attr_t topRight;
		attr_t bottomLeft;
		attr_t bottomRight;
		attr_t borderAttributes;
	} Border;

	typedef struct Window {
		WINDOW *ncursesWin;
		Point begin;
		Point end;
		//lets the program update screen only and only when required, skipping useless writes
		bool needsRefresh;
		//structure to hold border information
		Border border;
	} Window;

	Window newWindow (Point, Point, Border);
	
	void drawBorder (Window *);
	void deleteWindow (Window *);
	void hideBorder (Window *);
	void refreshWindow (Window *);
#endif //__WINDOW_H__
