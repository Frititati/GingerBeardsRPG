#ifndef PLAYER_H_
#define PLAYER_H_
#include "map.h"
#include "windows.h"

const int PLAYER_WIDTH = 3, PLAYER_HEIGHT = 3;


class Player {
public:
	void playerMovement(int, Map*&);
	void playerPossition(int*, int*);
	void draw(Map*&);
	void setAttack(int);
	int getHP();
	int getAttackStrength();
	int getMaxHP();
	int getDefense();
	void heal(int);
	bool damage(int);
	void attack(int);
	Player();
private:
	int xpossition;
	int ypossition;
	int attackDir;
	int attackCounter;
	int maxHP;
	int HP;
	int defense;
	int attackStrength;
};

#endif /* PLAYER_H_ */
