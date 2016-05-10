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


class Player {
public:
	void playerMovement(int, Map*&);
	void playerPossition(int*, int*);
	void draw(Map*&);
private:
	int xpossition = 3;
	int ypossition = 3;
};

#endif /* PLAYER_H_ */
