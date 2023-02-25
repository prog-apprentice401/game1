#include <stdio.h>
#include <ncurses.h>

#include "global.h"
#include "ship.h"
#include "colorPairs.h"
#include "window.h"

#define FPS 10

int main (int argc, char *argv[])
{
	clock_t clocksAtFrameUpdate = 0;

	initscr ();
	cbreak ();
	noecho ();
	curs_set (0);
	start_color ();
	keypad (stdscr, true);


	//from colorPairs.h
	initColorPairs ();

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

	//default border to use for windows
	Border defaultBorder = {ACS_HLINE, ACS_HLINE, ACS_VLINE, ACS_VLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER, COLOR_PAIR (WHITE_ON_BLACK) | A_DIM};
	Point begin = {0, 0};
	Point end = {LINES - 1, COLS};

	//create a seperate window for the game
	//as stdscr is used for messages and info
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

		if (ship.shipNeedsReprinting) {
			showShip (&gameWindow, &ship);
			ship.shipNeedsReprinting = false;
		}

		if (CLOCKS_TO_SEC (clock () - clocksAtFrameUpdate) >= 1.0/FPS && gameWindow.needsRefresh) {
			refreshWindow (&gameWindow);
			clocksAtFrameUpdate = clock ();
		}
	}

	destroyShip (&ship);
	deleteWindow (&gameWindow);
	endwin ();

	return errorStatus;
}
