#include <curses.h>
#include <stdio.h>
#include <ncurses.h>
#include <limits.h>
#include <time.h>

#include "global.h"
#include "ship.h"
#include "colorPairs.h"
#include "window.h"

#define FPS 10
#define MS_PER_FRAME (1.0/FPS)

int main (int argc, char *argv[])
{
	initscr ();
	cbreak ();
	noecho ();
	curs_set (0);
	start_color ();
	keypad (stdscr, true);

	//from colorPairs.h
	initColorPairs ();

	unsigned long long int msToFrameUpdate = 0;
	int errorStatus = 0;
	int ch;

	if (COLS < 40 || LINES < 20) {
		clear ();
		mvprintw (0, 0, "Screen is smaller than 80x30\n"
		                "Current dimensions: %dx%d"
		                " Press q to exit", COLS, LINES);
		refresh ();
		ch = getch ();

		endwin ();
		return -1;
	}

	Border defaultBorder = {ACS_HLINE, ACS_HLINE, ACS_VLINE, ACS_VLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER, COLOR_PAIR (WHITE_ON_BLACK) | A_DIM};
	Point begin = {0, 0};
	Point end = {LINES - 1, COLS};

	Window gameWindow = newWindow (begin, end, defaultBorder);
	Point shipSpawningPoint = {gameWindow.end.y - 3, (gameWindow.end.x - gameWindow.begin.x) / 2};
	Ship ship = newShip (shipSpawningPoint, 10, 20, 200, COLOR_PAIR (YELLOW_ON_BLACK) | A_BOLD);

	drawBorder (&gameWindow);
	showShip (&gameWindow, &ship);

	while ((ch = wgetch (gameWindow.ncursesWin)) != 'q') {
		switch (ch) {
			case KEY_LEFT: case 'h' :
				hideShip (&gameWindow, &ship);
				moveShipLeft (gameWindow.begin.x, gameWindow.end.x, &ship);
				break;

			case KEY_RIGHT: case 'l' :
				hideShip (&gameWindow, &ship);
				moveShipRight (gameWindow.begin.x, gameWindow.end.x, &ship);
				break;

			case ' ' : case 'k' : case '\n' :
				shoot (&ship);
				break;

			default:
				break;
		}
		
		hideBullets (&gameWindow, &ship);
		updateBullets (&gameWindow, &ship);
		showBullets (&gameWindow, &ship);

		showShip (&gameWindow, &ship);

		if (msToFrameUpdate <= 0) {
			msToFrameUpdate = MS_PER_FRAME;
			//refreshWindow(&gameWindow);
		}
		else {
			struct timespec timeBlock = {
				0,
				10000
			};
			nanosleep(&timeBlock, NULL);
		}
	}

	destroyShip (&ship);
	deleteWindow (&gameWindow);
	endwin ();

	return errorStatus;
}
