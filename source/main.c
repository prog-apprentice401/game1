#include <stdio.h>
#include <ncurses.h>

#include "global.h"
#include "ship.h"
#include "colorPairs.h"


int main (int argc, char *argv[])
{
	int errorStatus = 0;

	initscr ();
	cbreak ();
	noecho ();
	curs_set (0);
	timeout (0); //don't block for input
	start_color ();
	keypad (stdscr, true);

	WINDOW * window = stdscr;

	//from colorPairs.h
	initColorPairs ();

	uint32_t beg_y;
	uint32_t beg_x;

	uint32_t max_y;
	uint32_t max_x;

	int ch;

	getmaxyx (window, max_y, max_x);
	getbegyx (stdscr, beg_y, beg_x);

	getmaxyx (window, max_y, max_x);
	getbegyx (stdscr, beg_y, beg_x);

	if (max_x - beg_x < 80 || max_y - beg_y < 30) {
		wclear (window);
		mvwprintw (window, 0, 0, "Screen is smaller than 80x30\n"
			" Press q to exit");
		while ((ch = getch ()) != 'q')
			;

		endwin ();
		return -1;
	}
	Ship ship = newShip (window, (Point) {max_y - 3, (max_x - beg_x) / 2}, 10, 1);
	showShip (window, ship);

	while ((ch = wgetch (window)) && ch != 'q') {
		getmaxyx (window, max_y, max_x);
		getbegyx (stdscr, beg_y, beg_x);

		getmaxyx (window, max_y, max_x);
		getbegyx (stdscr, beg_y, beg_x);
		wborder (window, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
				ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

		attron (COLOR_PAIR (YELLOW_ON_BLACK) | A_BOLD);
		standend ();

		switch (ch) {
			case KEY_LEFT: case 'h':
				moveShipLeft (window, beg_x, max_x, &ship);	
				break;
			case KEY_RIGHT: case 'l':
				moveShipRight (window, beg_x, max_x, &ship);	
				break;
			case ' ': case 'k':
				//shoot (&ship);
				break;
			default:
				break;
		}
		wrefresh (window);
	}

	destroyShip (&ship);
	endwin ();

	return errorStatus;
}
