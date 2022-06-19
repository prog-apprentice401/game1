#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>

#include "global.h"
#include "ship.h"
#include "colorPairs.h"
#include "window.h"

Ship newShip (uint16_t init_y, uint16_t init_x, uint8_t maxBullets, uint8_t lives,
	attr_t shipAttributes)
{
	Ship ship;
	ship.position.y = init_y;
	ship.position.x = init_x;
	ship.lives = lives;
	ship.weapon.currentBullets = 0;
	ship.weapon.maxBullets = maxBullets;
	ship.weapon.bulletsArray = NULL;
	ship.weapon.bulletsNeedReprinting = false;
	ship.shipAttributes = shipAttributes;

	ship.weapon.bulletsArray = (Point *) calloc (maxBullets, sizeof (Point));
	
	//size is small enough for returning value
	return ship;
}

void destroyShip (Ship *shipPtr)
{
	free (shipPtr->weapon.bulletsArray);
	shipPtr->weapon.bulletsArray = NULL;
}

void showShip (Window *windowPtr, Ship *shipPtr)
{
	wattron (windowPtr->ncursesWin, shipPtr->shipAttributes);
	mvwaddch (windowPtr->ncursesWin, shipPtr->position.y, shipPtr->position.x, '*');
	mvwaddstr (windowPtr->ncursesWin, shipPtr->position.y + 1, shipPtr->position.x - 1,
		"/_\\");

	windowPtr->windowNeedsRefresh = true;
	shipPtr->shipNeedsReprinting = false;

	return;
}

void hideShip (Window *windowPtr, Ship *shipPtr)
{
	wstandend (windowPtr->ncursesWin);
	mvwaddch (windowPtr->ncursesWin, shipPtr->position.y, shipPtr->position.x, ' ');
	mvwaddstr (windowPtr->ncursesWin, shipPtr->position.y + 1, shipPtr->position.x - 1,
		"   ");

	windowPtr->windowNeedsRefresh = true;
	shipPtr->shipNeedsReprinting = true;

	return;
}

void moveShipRight (int16_t beg_x, int16_t max_x, Ship *shipPtr)
{
	shipPtr->position.x = (shipPtr->position.x < max_x - 3)
			? shipPtr->position.x + 1 : beg_x + 2;
	shipPtr->shipNeedsReprinting = true;
	return;
}

void moveShipLeft (int16_t beg_x, int16_t max_x, Ship *shipPtr)
{
	shipPtr->position.x = (shipPtr->position.x > beg_x + 2
			&& shipPtr->position.x < max_x - 2)
			? shipPtr->position.x - 1 : max_x - 3;
	shipPtr->shipNeedsReprinting = true;
	return;
}

void hideBullets (Window *windowPtr, Ship *shipPtr)
{
	Point *temp = shipPtr->weapon.bulletsArray;

	for (int i = 0; i < shipPtr->weapon.currentBullets; i++) {
		mvwaddch (windowPtr->ncursesWin, temp[i].y, temp[i].x, ACS_DIAMOND);
	}

	windowPtr->windowNeedsRefresh = true;
	shipPtr->weapon.bulletsNeedReprinting = true;
	return;
}

void showBullets (Window *windowPtr, Ship *shipPtr)
{
	Point *temp = shipPtr->weapon.bulletsArray;

	for (int i = 0; i < shipPtr->weapon.currentBullets; i++) {
		mvwaddch (windowPtr->ncursesWin, temp[i].y, temp[i].x, ACS_DIAMOND);
	}

	windowPtr->windowNeedsRefresh = true;
	shipPtr->weapon.bulletsNeedReprinting = false;

	return;
}

void shoot (Ship *shipPtr)
{
	if (shipPtr->weapon.currentBullets >= shipPtr->weapon.maxBullets) {
		return;
	}
	uint8_t newBulletIndex = shipPtr->weapon.currentBullets;

	shipPtr->weapon.bulletsArray[newBulletIndex].y = shipPtr->position.y - 1;
	shipPtr->weapon.bulletsArray[newBulletIndex].x = shipPtr->position.x;

	shipPtr->weapon.currentBullets++;
	shipPtr->weapon.bulletsNeedReprinting = true;
}
