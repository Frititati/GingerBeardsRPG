#include "Player.h"
#include "GingerBeards.h"
#include <iostream>
using namespace std;

char** playerLook;
Map* mapDraw;

Player::Player() {
	playerLook = new char *[PLAYER_HEIGHT];
	for (int i = 0; i < PLAYER_HEIGHT; i++) {
		playerLook[i] = new char[PLAYER_WIDTH];
	}
//	(°_ʖ°)
//	EMPTY o EMPTY
	playerLook[0][0] = '^';
	playerLook[0][1] = '_';
	playerLook[0][2] = '^';
	playerLook[1][0] = '/';
	playerLook[1][1] = '|';
	playerLook[1][2] = '\\';
	playerLook[2][0] = '/';
	playerLook[2][1] = EMPTY;
	playerLook[2][2] = '\\';

	xpossition = 5;
	ypossition = 25;
	attackCounter = 0;
	attackDir = 8;
}

void Player::playerMovement(int keypressed, Map*& mapEditor) {
	int tempx = xpossition;
	int tempy = ypossition;
	switch (keypressed) {
	case 1:
		xpossition--;
		playerLook[0][0] = '<';
		playerLook[0][1] = '_';
		playerLook[0][2] = '<';
		break;
	case 2:
		xpossition++;
		playerLook[0][0] = '>';
		playerLook[0][1] = '_';
		playerLook[0][2] = '>';
		break;
	case 3:
		ypossition--;
		playerLook[0][0] = '>';
		playerLook[0][1] = '_';
		playerLook[0][2] = '<';
		break;
	case 4:
		ypossition++;
		playerLook[0][0] = '>';
		playerLook[0][1] = '_';
		playerLook[0][2] = '<';
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
	mapDraw = mapEditor;
	mapEditor->drawCharacter(xpossition, ypossition, PLAYER_WIDTH,PLAYER_HEIGHT, playerLook);
	if(attackDir == 8){
		attack(8);
	}else{
		attack(attackDir);
	}
}
void Player::setAttack(int direction){
	if(attackCounter == 0){
		attackDir = direction;
	}
}
void Player::attack(int direction){

	if(direction == 1){//a
		playerLook[1][0] = '-';
		if(attackCounter ==0){
			mapDraw->editBorder(xpossition-1, ypossition+2, '6');
			mapDraw->editBorder(xpossition-2, ypossition+1, '6');
			mapDraw->editBorder(xpossition-2, ypossition, '6');
			mapDraw->editBorder(xpossition-2, ypossition-1, '6');
			mapDraw->editBorder(xpossition-1, ypossition-2, '6');
		}
		attackCounter++;
		switch(attackCounter){
			case 1:
				mapDraw->drawChar(xpossition-1, ypossition+2, '/');
			break;
			case 2:
				mapDraw->drawChar(xpossition-2, ypossition+1, '-');
			break;
			case 3:
				mapDraw->drawChar(xpossition-2, ypossition, '-');
			break;
			case 4:
				mapDraw->drawChar(xpossition-2, ypossition-1, '-');
			break;
			case 5:
				mapDraw->drawChar(xpossition-1, ypossition-2, '\\');
			break;
			case 6:
				attackCounter = 0;
				mapDraw->restoreBorder();
				playerLook[1][0] = '/';
			break;
		}
	}else if(direction == 2){//d
		playerLook[1][2] = '-';
		if(attackCounter ==0){
			mapDraw->editBorder(xpossition+1, ypossition-2, '6');
			mapDraw->editBorder(xpossition+2, ypossition-1, '6');
			mapDraw->editBorder(xpossition+2, ypossition, '6');
			mapDraw->editBorder(xpossition+2, ypossition+1, '6');
			mapDraw->editBorder(xpossition+1, ypossition+2, '6');
		}
		attackCounter++;
		switch(attackCounter){
			case 1:
				mapDraw->drawChar(xpossition+1, ypossition-2, '/');
			break;
			case 2:
				mapDraw->drawChar(xpossition+2, ypossition-1, '-');
			break;
			case 3:
				mapDraw->drawChar(xpossition+2, ypossition, '-');
			break;
			case 4:
				mapDraw->drawChar(xpossition+2, ypossition+1, '-');
			break;
			case 5:
				mapDraw->drawChar(xpossition+1, ypossition+2, '\\');
			break;
			case 6:
				attackCounter = 0;
				mapDraw->restoreBorder();
				playerLook[1][2] = '\\';
			break;
		}
	}else if(direction == 3){//w
		if(attackCounter ==0){
			mapDraw->editBorder(xpossition-2, ypossition-1, '6');
			mapDraw->editBorder(xpossition-1, ypossition-2, '6');
			mapDraw->editBorder(xpossition, ypossition-2, '6');
			mapDraw->editBorder(xpossition+1, ypossition-2, '6');
			mapDraw->editBorder(xpossition+2, ypossition-1, '6');
		}
		attackCounter++;
		switch(attackCounter){
			case 1:
				mapDraw->drawChar(xpossition-2, ypossition-1, '\\');
			break;
			case 2:
				mapDraw->drawChar(xpossition-1, ypossition-2, '\\');
			break;
			case 3:
				mapDraw->drawChar(xpossition, ypossition-2, '|');
			break;
			case 4:
				mapDraw->drawChar(xpossition+1, ypossition-2, '/');
			break;
			case 5:
				mapDraw->drawChar(xpossition+2, ypossition-1, '/');
			break;
			case 6:
				attackCounter = 0;
				mapDraw->restoreBorder();
			break;
		}
	}else if(direction == 4){//s
		if(attackCounter ==0){
			mapDraw->editBorder(xpossition+2, ypossition+1, '6');
			mapDraw->editBorder(xpossition+1, ypossition+2, '6');
			mapDraw->editBorder(xpossition, ypossition+2, '6');
			mapDraw->editBorder(xpossition-1, ypossition+2, '6');
			mapDraw->editBorder(xpossition-2, ypossition+1, '6');
		}
		attackCounter++;
		switch(attackCounter){
			case 1:
				mapDraw->drawChar(xpossition+2, ypossition+1, '\\');
			break;
			case 2:
				mapDraw->drawChar(xpossition+1, ypossition+2, '\\');
			break;
			case 3:
				mapDraw->drawChar(xpossition, ypossition+2, '|');
			break;
			case 4:
				mapDraw->drawChar(xpossition-1, ypossition+2, '/');
			break;
			case 5:
				mapDraw->drawChar(xpossition-2, ypossition+1, '/');
			break;
			case 6:
				attackCounter = 0;
				mapDraw->restoreBorder();
			break;
		}
	} else if(direction == 5){//aoe f1
		attackCounter++;
		switch(attackCounter){
			case 1:
				mapDraw->drawChar(xpossition-1, ypossition-2, 'c');
				mapDraw->drawChar(xpossition, ypossition-2, 'c');
				mapDraw->drawChar(xpossition+1, ypossition-2, 'c');
				mapDraw->drawChar(xpossition-1, ypossition+2, 'c');
				mapDraw->drawChar(xpossition, ypossition+2, 'c');
				mapDraw->drawChar(xpossition+1, ypossition+2, 'c');
				mapDraw->drawChar(xpossition+2, ypossition-1, 'c');
				mapDraw->drawChar(xpossition+2, ypossition, 'c');
				mapDraw->drawChar(xpossition+2, ypossition+1, 'c');
				mapDraw->drawChar(xpossition-2, ypossition-1, 'c');
				mapDraw->drawChar(xpossition-2, ypossition, 'c');
				mapDraw->drawChar(xpossition-2, ypossition+1, 'c');
			break;
			case 2:
				mapDraw->drawChar(xpossition-1, ypossition-2, 'c');
				mapDraw->drawChar(xpossition, ypossition-2, 'c');
				mapDraw->drawChar(xpossition+1, ypossition-2, 'c');
				mapDraw->drawChar(xpossition-1, ypossition+2, 'c');
				mapDraw->drawChar(xpossition, ypossition+2, 'c');
				mapDraw->drawChar(xpossition+1, ypossition+2, 'c');
				mapDraw->drawChar(xpossition+2, ypossition-1, 'c');
				mapDraw->drawChar(xpossition+2, ypossition, 'c');
				mapDraw->drawChar(xpossition+2, ypossition+1, 'c');
				mapDraw->drawChar(xpossition-2, ypossition-1, 'c');
				mapDraw->drawChar(xpossition-2, ypossition, 'c');
				mapDraw->drawChar(xpossition-2, ypossition+1, 'c');
				mapDraw->drawChar(xpossition-1, ypossition-3, 'c');
				mapDraw->drawChar(xpossition, ypossition-3, 'c');
				mapDraw->drawChar(xpossition+1, ypossition-3, 'c');
				mapDraw->drawChar(xpossition+2, ypossition-2, 'c');
				mapDraw->drawChar(xpossition-1, ypossition+3, 'c');
				mapDraw->drawChar(xpossition, ypossition+3, 'c');
				mapDraw->drawChar(xpossition+1, ypossition+3, 'c');
				mapDraw->drawChar(xpossition+2, ypossition+2, 'c');
				mapDraw->drawChar(xpossition+3, ypossition-1, 'c');
				mapDraw->drawChar(xpossition+3, ypossition, 'c');
				mapDraw->drawChar(xpossition+3, ypossition+1, 'c');
				mapDraw->drawChar(xpossition-2, ypossition+2, 'c');
				mapDraw->drawChar(xpossition-3, ypossition-1, 'c');
				mapDraw->drawChar(xpossition-3, ypossition, 'c');
				mapDraw->drawChar(xpossition-3, ypossition+1, 'c');
				mapDraw->drawChar(xpossition-2, ypossition-2, 'c');
			break;
			case 3:
				//mapDraw->drawChar(xpossition, ypossition+2, '|');
			break;
			case 4:
				//mapDraw->drawChar(xpossition-1, ypossition+2, '/');
			break;
			case 5:
				//mapDraw->drawChar(xpossition-2, ypossition+1, '/');
			break;
			case 6:
				attackCounter = 0;
			break;
		}
	}

	if(attackCounter == 0){
		attackDir = 8;
	}
}
