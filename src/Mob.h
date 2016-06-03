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
#include "GingerBeards.h"

const int MOB_HEIGHT = 1, MOB_WIDTH = 3;
const int BOSS_HEIGHT = 5, BOSS_WIDTH = 9;
const int BOSS_MAX_HP = 5000;
const int BOSS_HEAL_RATE = 5;

class Mob {
public:
	void creatingMob(int, int, Player*&);
	void createBoss(int, int);
	void mobMovement(Map*&, Player*&);
	void detectDamage(Map*&);
	int getHealth();
	int getPowerAddLoot();
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
	int xposition;
	int yposition;
	int height, width;
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
	int maxPowerAddLoot;
	char** mobLook;
};

#endif /* SRC_MOB_H_ */
