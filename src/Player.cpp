#include "Player.h"
#include "GingerBeards.h"
#include <windows.h>
#include <iostream>
using namespace std;

char** playerLook;

Player::Player() {
	playerLook = new char *[PLAYER_HEIGHT];
	for (int i = 0; i < PLAYER_HEIGHT; i++) {
		playerLook[i] = new char[PLAYER_WIDTH];
	}
	playerLook[0][0] = EMPTY;
	playerLook[0][1] = 'o';
	playerLook[0][2] = EMPTY;

	playerLook[1][0] = '/';
	playerLook[1][1] = '|';
	playerLook[1][2] = '\\';
	playerLook[2][0] = '/';
	playerLook[2][1] = EMPTY;
	playerLook[2][2] = '\\';
	xpossition = 5;
	ypossition = 10;
}

void Player::playerMovement(int keypressed, Map*& mapEditor) {
	int tempx = xpossition;
	int tempy = ypossition;
	switch (keypressed) {
	case 1:
		xpossition--;
		break;
	case 2:
		xpossition++;
		break;
	case 3:
		ypossition--;
		break;
	case 4:
		ypossition++;
		break;
	case 5:
		break;
	}
	if (!mapEditor->testBorder(xpossition, ypossition, PLAYER_WIDTH, PLAYER_HEIGHT, playerLook)) {
		xpossition = tempx;
		ypossition = tempy;
	}

}

void Player::playerPossition(int* x, int* y) {
	*x = xpossition;
	*y = ypossition;
}

void Player::draw(Map*& mapEditor) {
	mapEditor->drawCharacter(xpossition, ypossition, PLAYER_WIDTH,
			PLAYER_HEIGHT, playerLook);
}
