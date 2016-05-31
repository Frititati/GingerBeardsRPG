#ifndef PLAYER_H_
#define PLAYER_H_
#include "map.h"
#include "windows.h"

const int PLAYER_WIDTH = 3, PLAYER_HEIGHT = 3;


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
	void setHP(int);
	void addHP(int);
	void addDef(int);
	void addAtk(int);
	void heal();
	bool hasDied();
	void teleport(int, int);
	bool damage(int);
	void attack(int);
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
};

#endif /* PLAYER_H_ */
