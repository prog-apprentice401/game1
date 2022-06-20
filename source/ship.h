#include <ncurses.h>
#include <time.h>
#include "window.h"
#include "global.h"

#ifndef __SHIP_H__
	#define __SHIP_H__
	typedef struct Bullet {
		Point position;
		clock_t positionLastUpdatedAtClock;
	} Bullet;

	typedef struct Ship {
		Point position;
		uint8_t lives;
		struct Weapon {
			uint8_t currentBullets;
			uint8_t maxBullets;
			//will be allocated at runtime in memory
			Bullet *bulletsArray;
			_Bool bulletsNeedReprinting;
		} weapon;
		attr_t shipAttributes;
		_Bool shipNeedsReprinting;
	} Ship;

	Ship newShip (uint16_t, uint16_t, uint8_t, uint8_t, attr_t shipAttributes);
	void destroyShip (Ship *);
	void showShip (Window *, Ship *);
	void hideShip (Window *, Ship *);
	void moveShipRight (int16_t, int16_t, Ship *);
	void moveShipLeft (int16_t, int16_t, Ship *);

	void shoot (Ship *);
	void hideBullets (Window *, Ship *);
	void showBullets (Window *, Ship *);
#endif //__SHIP_H__
