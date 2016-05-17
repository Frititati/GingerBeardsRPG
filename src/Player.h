/*
 * Player.h
 *
 *  Created on: 25.04.2016
 *      Author: Michele
 */

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
	void attack(int);
	Player();
private:
	int xpossition;
	int ypossition;
	int attackDir = 8;
	int testchar = 0;
};

#endif /* PLAYER_H_ */
