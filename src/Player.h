#ifndef PLAYER_H_
#define PLAYER_H_
#include "Map.h"
#include "windows.h"

const int PLAYER_WIDTH = 3, PLAYER_HEIGHT = 3;
// half of the vertical diagonal
const int AOE_RADIUS = YINCREASE / 3;
const char AOE_CHAR= '~';
const int MINIMUM_AOE_COST = 1;

class Player {
public:
	void playerMovement(int, Map*&);
	void playerPosition(int*, int*);
	void draw(Map*&);
	void setAttack(int);
	int getHP();
	int getAttackStrength();
	int getMaxHP();
	int getDefense();
	int getAOEDamage();
	int getMaxPower();
	void setHP(int);
	void addHP(int);
	void addDef(int);
	void addAtk(int);
	void addMaxPower(int);
	void increasePower();
	void heal();
	bool hasDied();
	void teleport(int, int);
	bool damage(int);
	int getPower();
	void attack(int);
	void setMaxHP(int);
	void standardLook();
	void loadCharacter(int, int, int, int, int, int, int, int);
	void AOEAttack();
	void leftSwing();
	void rightSwing();
	void frontSwing();
	void backSwing();
	Player();
private:
	int xposition;
	int yposition;
	int attackDir;
	int attackCounter;
	int maxHP;
	int HP;
	int defense;
	int attackStrength;
	int healPerSec;
	int healDelaySec;
	int power;
	int maxPower;
	int aoeDamage;
};

#endif /* PLAYER_H_ */
