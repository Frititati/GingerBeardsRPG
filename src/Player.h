/*
 * Player.h
 *
 *  Created on: 25.04.2016
 *      Author: Michele
 */

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
private:
	int x, y;
	int xSpeed, ySpeed;
	char portrait[];
public:
	Player(int, int, char[]);

	/*
	 * True if the player moved (false if the player position
	 */
	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();
	virtual ~Player();
};

#endif /* PLAYER_H_ */
