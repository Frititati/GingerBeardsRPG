#ifndef PLAYER_H_
#define PLAYER_H_
#include "Map.h"

const int PLAYER_WIDTH = 3, PLAYER_HEIGHT = 3;


class Player {
public:
	void playerMovement(int, Map*&);
	void playerPossition(int*, int*);
	void draw(Map*&);
	void setAttack(int);
	void attack(int);
	Player();
private:
	int xpossition;
	int ypossition;
	int attackDir;
	int attackCounter;
};

#endif /* PLAYER_H_ */
