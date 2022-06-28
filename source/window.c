#include <stdio.h>
#include <ncurses.h>

#include "window.h"

Window newWindow (int16_t begin_y, int16_t begin_x, int16_t max_y, int16_t max_x,
	attr_t top, attr_t bottom, attr_t right, attr_t left, attr_t topLeft,
	attr_t topRight, attr_t bottomLeft, attr_t bottomRight, attr_t borderAttributes)
{
	Window localwin;
	localwin.ncursesWin = newwin (max_y - begin_y, max_x - begin_x, begin_y, begin_x);
	keypad (localwin.ncursesWin, true);
	
	//wait for 100 ms, so loop is blocked just enough to
	//ease things for CPU
	wtimeout (localwin.ncursesWin, 100);
	curs_set (0);

	localwin.begin.y = begin_y;
	localwin.begin.x = begin_x;
	localwin.end.y = max_y;
	localwin.end.x = max_x;
	
	localwin.windowNeedsRefresh = false;

	localwin.border.top = top;
	localwin.border.bottom = bottom;
	localwin.border.left = left;
	localwin.border.right = right;
	localwin.border.topLeft = topLeft;
	localwin.border.topRight = topRight;
	localwin.border.bottomLeft = bottomLeft;
	localwin.border.bottomRight = bottomRight;

	localwin.border.borderAttributes = borderAttributes;	

	return localwin;
}

void drawBorder (Window *window)
{
	wborder (window->ncursesWin, window->border.left, window->border.right,
		window->border.top, window->border.bottom, window->border.topLeft,
		window->border.topRight, window->border.bottomLeft,
		window->border.bottomRight);
	window->windowNeedsRefresh = true;

	return;
}

void hideBorder (Window *window)
{
	wborder (window->ncursesWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	window->windowNeedsRefresh = true;

	return;
}

void deleteWindow (Window *window)
{
	delwin (window->ncursesWin);
	window->begin.x = -1;
	window->end.x = -1;

	return;
}

void refreshWindow (Window *window)
{
	wrefresh (window->ncursesWin);
	window->windowNeedsRefresh = false;

	return;
}
