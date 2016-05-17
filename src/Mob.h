/*
 * Mob.h
 *
 *  Created on: 7 May 2016
 *      Author: Filippo M Cardano
 */

#ifndef SRC_MOB_H_
#define SRC_MOB_H_
#include "map.h"
#include "player.h"

const int MOB_HEIGHT = 1, MOB_WIDTH = 3;

class Mob {
public:
	void mobMovement(Map*&, Player*&);
	bool testTouch();
	Mob();
private:
	int xpossition;
	int ypossition;
	int oldx;
	int oldy;
	int speedCount;
	int speed;
	int viewDistance; // sqrt(10)
};

#endif /* SRC_MOB_H_ */
