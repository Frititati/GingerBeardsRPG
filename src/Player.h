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
	Player();
	int playerMovement(int, Map, HWND);
};

#endif /* PLAYER_H_ */
