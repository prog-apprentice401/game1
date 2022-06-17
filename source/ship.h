#include <ncurses.h>
#include "global.h"

#ifndef __SHIP_H__
	#define __SHIP_H__

	typedef struct Weapon {
		uint8_t currentBullets;
		uint8_t maxBullets;
		//will be allocated at runtime in memory
		Point * bulletsArray;
	} Weapon;

	typedef struct Ship {
		Point position;
		uint8_t lives;
		Weapon weapon;
	} Ship;

	Ship newShip (WINDOW *, Point, uint8_t, uint8_t);
	void destroyShip (Ship *);
	void showShip (WINDOW *, Ship);
	void hideShip (WINDOW *, Ship);
	void moveShipRight (WINDOW *, uint32_t, uint32_t, Ship *);
	void moveShipLeft (WINDOW *, uint32_t, uint32_t, Ship *);
#endif //__SHIP_H__
