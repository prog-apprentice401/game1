#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include "global.h"
#include "ship.h"
#include "colorPairs.h"

Ship newShip (WINDOW *window, Point initPosition, uint8_t maxBullets, uint8_t lives)
{
	uint8_t begin_x;
	uint8_t begin_y;
	getbegyx (window, begin_y, begin_x);

	uint8_t max_x;
	uint8_t max_y;
	getmaxyx (window, max_y, max_x);

	//start the ship in the center
	Ship ship;
	ship.position.y = initPosition.y;
	ship.position.x = initPosition.x;
	ship.lives = lives;
	ship.weapon.currentBullets = 0;
	ship.weapon.maxBullets = maxBullets;
	ship.weapon.bulletsArray = NULL;

	ship.weapon.bulletsArray = (Point *) calloc (maxBullets, sizeof (Point));
	
	//size is small enough for returning value
	return ship;
}

void destroyShip (Ship *shipPtr)
{
	free (shipPtr->weapon.bulletsArray);
	shipPtr->weapon.bulletsArray = 0;
}

void showShip (WINDOW *window, Ship ship)
{
	mvwprintw (window, ship.position.y - 1, ship.position.x, "*");
	mvwprintw (window, ship.position.y, ship.position.x - 1, "/_\\");

	return;
}

void hideShip (WINDOW *window, Ship ship)
{
	mvwprintw (window, ship.position.y - 1, ship.position.x, " ");
	mvwprintw (window, ship.position.y, ship.position.x - 1, "   ");

	return;
}

void moveShipRight (WINDOW *window, uint32_t beg_x, uint32_t max_x, Ship *shipPtr)
{
	hideShip (window, *shipPtr);
	shipPtr->position.x = (shipPtr->position.x < max_x - 3)
				? shipPtr->position.x + 1 : beg_x + 2;
	attron (COLOR_PAIR (YELLOW_ON_BLACK) | A_BOLD);
	showShip (window, *shipPtr);
	standend ();

	return;
}

void moveShipLeft (WINDOW *window, uint32_t beg_x, uint32_t max_x, Ship *shipPtr)
{
	hideShip (window, *shipPtr);
	shipPtr->position.x = (shipPtr->position.x > beg_x + 2
			&& shipPtr->position.x < max_x - 2)
				? shipPtr->position.x - 1 : max_x - 3;
	attron (COLOR_PAIR (YELLOW_ON_BLACK) | A_BOLD);
	showShip (window, *shipPtr);
	standend ();

	return;
}
