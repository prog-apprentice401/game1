#include "global.h"

#ifndef __WINDOW_H__
	#define __WINDOW_H__

	typedef struct Window {
		WINDOW *ncursesWin;
		Point begin;
		Point end;
		bool windowNeedsRefresh;
		//structure to hold border information
		struct Border {
			attr_t top;
			attr_t bottom;
			attr_t right;
			attr_t left;
			attr_t topLeft;
			attr_t topRight;
			attr_t bottomLeft;
			attr_t bottomRight;
			attr_t borderAttributes;
		} border;
	} Window;

	//The first four are coordinates, the next eight are border characters
	Window newWindow (int16_t, int16_t, int16_t, int16_t,
			attr_t, attr_t, attr_t, attr_t, attr_t,
			attr_t, attr_t, attr_t, attr_t);
	
	void drawBorder (Window *);
	void deleteWindow (Window *);
	void hideBorder (Window *);
	void refreshWindow (Window *);
#endif //__WINDOW_H__
