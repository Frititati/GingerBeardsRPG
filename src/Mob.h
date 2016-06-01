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
	void creatingMob(int, int, Player*&);
	void mobMovement(Map*&, Player*&);
	void detectDamage(Map*&);
	int getHealth();
	int RTD(int , int );
	void setLook(int);
	void setStats(int, int, Player*&);
//	void setStats(Player*&, int);
	int getHealthLoot();
	int getDefenceLoot();
	int getAttackLoot();
	int getHealthAddLoot();
	bool despawnCheck();
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
	int defenceLoot;
	int attackLoot;
	int healthLoot;
	int healthAddLoot;
	char** mobLook;
};

#endif /* SRC_MOB_H_ */
