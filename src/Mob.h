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

class Mob {
public:
	void mobMovement(Map*&, Player*&);
private:
	int xpossition = 20;
	int ypossition = 35;
	int oldx;
	int oldy;
};

#endif /* SRC_MOB_H_ */
