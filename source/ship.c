#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <time.h>

#include "global.h"
#include "ship.h"
#include "colorPairs.h"
#include "window.h"

Ship newShip (Point spawningPoint, uint8_t maxBullets, uint8_t bulletSpeed, uint8_t lives, attr_t shipAttributes)
{
	Ship ship;
	ship.position.y = spawningPoint.y;
	ship.position.x = spawningPoint.x;
	ship.lives = lives;
	ship.weapon.currentBullets = 0;
	ship.weapon.maxBullets = maxBullets;
	ship.weapon.bulletSpeed = bulletSpeed;
	ship.weapon.bulletsArray = NULL;
	ship.weapon.bulletsNeedReprinting = false;
	ship.shipAttributes = shipAttributes;

	ship.weapon.bulletsArray = calloc (maxBullets, sizeof (Bullet));
	
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
	mvwaddch (windowPtr->ncursesWin, shipPtr->position.y, shipPtr->position.x, '^');
	mvwaddstr (windowPtr->ncursesWin, shipPtr->position.y + 1, shipPtr->position.x - 1, "/_\\");

	windowPtr->needsRefresh = true;
	shipPtr->shipNeedsReprinting = false;

	return;
}

void hideShip (Window *windowPtr, Ship *shipPtr)
{
	mvwaddch (windowPtr->ncursesWin, shipPtr->position.y, shipPtr->position.x, ' ');
	mvwaddstr (windowPtr->ncursesWin, shipPtr->position.y + 1, shipPtr->position.x - 1, "   ");

	windowPtr->needsRefresh = true;
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
	for (int i = 0; i < shipPtr->weapon.currentBullets; i++) {
		mvwaddch (windowPtr->ncursesWin, shipPtr->weapon.bulletsArray[i].position.y,
			shipPtr->weapon.bulletsArray[i].position.x, ' ');
	}

	windowPtr->needsRefresh = true;
	shipPtr->weapon.bulletsNeedReprinting = true;
	return;
}

void showBullets (Window *windowPtr, Ship *shipPtr)
{
	for (int i = 0; i < shipPtr->weapon.currentBullets; i++) {
		mvwaddch (windowPtr->ncursesWin, shipPtr->weapon.bulletsArray[i].position.y,
			shipPtr->weapon.bulletsArray[i].position.x, '*' | COLOR_PAIR (YELLOW_ON_BLACK) | A_BOLD);
	}

	windowPtr->needsRefresh = true;
	shipPtr->weapon.bulletsNeedReprinting = false;

	return;
}

void shoot (Ship *shipPtr)
{
	if (shipPtr->weapon.currentBullets >= shipPtr->weapon.maxBullets) {
		return;
	}
	uint8_t newBulletIndex = shipPtr->weapon.currentBullets;

	shipPtr->weapon.bulletsArray[newBulletIndex].position.y = shipPtr->position.y - 1;
	shipPtr->weapon.bulletsArray[newBulletIndex].position.x = shipPtr->position.x;
	shipPtr->weapon.bulletsArray[newBulletIndex].clocksAtBulletUpdate = clock ();

	shipPtr->weapon.currentBullets++;
	shipPtr->weapon.bulletsNeedReprinting = true;
}

void deleteBullet (Weapon * weaponPtr, uint8_t bulletIndex)
{
	for (int i = bulletIndex; i < weaponPtr->currentBullets - 1; i++) {
		weaponPtr->bulletsArray[i] = weaponPtr->bulletsArray[i + 1];
	}
	weaponPtr->currentBullets--;
}

void updateBullets (Weapon *weaponPtr, Window * gameWindow)
{
	clock_t currentTime;

	for (int i = 0; i < weaponPtr->currentBullets; i++) {
		currentTime = clock ();
		if ((currentTime - weaponPtr->bulletsArray[i].clocksAtBulletUpdate) >= CLOCKS_PER_SEC/weaponPtr->bulletSpeed) {
			weaponPtr->bulletsArray[i].position.y -= 1;
			weaponPtr->bulletsArray[i].clocksAtBulletUpdate = clock ();
		}

		if (weaponPtr->bulletsArray[i].position.y <= 0)  {
			deleteBullet (weaponPtr, i);
		}
	}
}
