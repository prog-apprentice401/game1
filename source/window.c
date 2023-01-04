#include <stdio.h>
#include <ncurses.h>

#include "window.h"
#include "global.h"

Window newWindow (Point begin, Point end, Border border)
{
	Window localwin;
	localwin.ncursesWin = newwin (end.y - begin.y, end.x - begin.x, begin.y, begin.x);
	keypad (localwin.ncursesWin, true);
	
	//wait for 100 ms, so loop is blocked just enough to
	//ease things for CPU
	wtimeout (localwin.ncursesWin, 0);
	curs_set (0);

	localwin.begin.y = begin.y;
	localwin.begin.x = begin.x;
	localwin.end.y = end.y;
	localwin.end.x = end.x;
	
	localwin.needsRefresh = false;

	localwin.border.top = border.top;
	localwin.border.bottom = border.bottom;
	localwin.border.left = border.left;
	localwin.border.right = border.right;
	localwin.border.topLeft = border.topLeft;
	localwin.border.topRight = border.topRight;
	localwin.border.bottomLeft = border.bottomLeft;
	localwin.border.bottomRight = border.bottomRight;

	localwin.border.borderAttributes = border.borderAttributes;	

	return localwin;
}

void drawBorder (Window *window)
{
	wborder (window->ncursesWin, window->border.left, window->border.right,
		window->border.top, window->border.bottom, window->border.topLeft,
		window->border.topRight, window->border.bottomLeft,
		window->border.bottomRight);
	window->needsRefresh = true;

	return;
}

void hideBorder (Window *window)
{
	wborder (window->ncursesWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	window->needsRefresh = true;

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
	window->needsRefresh = false;

	return;
}
