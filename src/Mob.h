/*
 * Mob.h
 *
 *  Created on: 7 May 2016
 *      Author: Filippo M Cardano
 */

#ifndef SRC_MOB_H_
#define SRC_MOB_H_
#include "Map.h"
#include "Player.h"

const int MOB_HEIGHT = 1, MOB_WIDTH = 3;

class Mob {
public:
	void creatingMob(int, int);
	void mobMovement(Map*&, Player*&);
	void detectDamage(Map*&);
	int getHealth();
	Mob();
	~Mob();
private:
	int xpossition;
	int ypossition;
	int differencex;
	int differencey;
	int hp;
	int attackStrength;
	int speedCount;
	int speed;
	int viewDistance;
	bool aggressive;
};

#endif /* SRC_MOB_H_ */
