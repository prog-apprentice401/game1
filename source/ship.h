#include <ncurses.h>
#include <time.h>

#include "window.h"
#include "global.h"

#ifndef __SHIP_H__
	#define __SHIP_H__

	typedef struct Bullet {
		Point position;
		clock_t clocksAtBulletUpdate;
	} Bullet;

	typedef struct Weapon {
		uint8_t currentBullets;
		uint8_t maxBullets;
		//in cells-per-second
		uint8_t bulletSpeed;
		//will be allocated at runtime in memory
		Bullet *bulletsArray;
	} Weapon;

	typedef struct Ship {
		Point position;
		uint8_t lives;
		Weapon weapon;
		attr_t shipAttributes;
		//bool from ncurses
		bool shipNeedsReprinting;
	} Ship;

	Ship newShip (Point, uint8_t, uint8_t, uint8_t, attr_t);
	void destroyShip (Ship *);
	void showShip (Window *, Ship *);
	void hideShip (Window *, Ship *);
	void moveShipRight (int16_t, int16_t, Ship *);
	void moveShipLeft (int16_t, int16_t, Ship *);

	void shoot (Ship *);
	void deleteBullet (Weapon *, uint8_t);
	void hideBullets (Window *, Ship *);
	void showBullets (Window *, Ship *);
	void updateBullets (Window *, Ship *);
#endif //__SHIP_H__
