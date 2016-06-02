#include "Player.h"
#include "GingerBeards.h"
#include <windows.h>
#include <iostream>
using namespace std;

char** playerLook;
Map* mapDraw;

bool isDead;

Player::Player() {
	isDead = false;
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

	xposition = 396;
	yposition = 162;
	attackCounter = 0;
	attackDir = 8;
	maxHP = 600;
	HP = 500;
	defense = 1;
	attackStrength = 10;
	healPerSec = 1;
	healDelaySec = 0;
}

void Player::playerMovement(int keypressed, Map*& mapEditor) {
	int tempx = xposition;
	int tempy = yposition;
	if (isDead)
		return;
	switch (keypressed) {
	case 1:
		xposition--;
		playerLook[0][0] = '<';
		playerLook[0][1] = '_';
		playerLook[0][2] = '<';
		break;
	case 2:
		xposition++;
		playerLook[0][0] = '>';
		playerLook[0][1] = '_';
		playerLook[0][2] = '>';
		break;
	case 3:
		yposition--;
		playerLook[0][0] = '>';
		playerLook[0][1] = '_';
		playerLook[0][2] = '<';
		break;
	case 4:
		yposition++;
		playerLook[0][0] = '>';
		playerLook[0][1] = '_';
		playerLook[0][2] = '<';
		break;
	}

	if (!mapEditor->testBorder(xposition, yposition, PLAYER_WIDTH, PLAYER_HEIGHT, playerLook)) {
		xposition = tempx;
		yposition = tempy;
	}
}

void Player::heal() {
	if(healDelaySec <= 0){
		if (!isDead) {
			HP = min(maxHP, HP + healPerSec);
		}
	}else{
		healDelaySec--;
	}
}

bool Player::hasDied() {
	return isDead;
}

// true if the player still lives
bool Player::damage(int amount) {
	int damage = amount <= defense ? 1 : amount - defense;
	HP -= damage;
	healDelaySec = 2 * 1000/GAME_DELAY_MS;
	if (HP <= 0) {
		playerLook[0][0] = 'x';
		playerLook[0][2] = 'x';
		isDead = true;
		return false;
	}
	return true;
}

void Player::playerPosition(int* x, int* y) {
	*x = xposition;
	*y = yposition;
}

void Player::draw(Map*& mapEditor) {
	mapDraw = mapEditor;
	mapEditor->drawCharacter(xposition, yposition, PLAYER_WIDTH,PLAYER_HEIGHT, playerLook);
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

int Player::getHP() {
	return HP;
}

int Player::getMaxHP() {
	return maxHP;
}

int Player::getAttackStrength() {
	return attackStrength;
}

int Player::getDefense() {
	return defense;
}
void Player::addHP(int amount) {
	int max = maxHP - HP;
		if(max <= amount){
			this->HP = maxHP;
		}else{
			this->HP = HP + amount;
		}
}
void Player::addDef(int def) {
	this->defense += def;
}
void Player::addAtk(int atk) {
	this->attackStrength += atk;
}

void Player::setHP(int amount) {
	this->HP = amount;
}

void Player::setMaxHP(int amount){
	this->maxHP = amount;
}

void Player::teleport(int x, int y) {
	xposition = x;
	yposition = y;
}

void Player::attack(int direction){
	if (isDead)
		return;
	if(direction == 1){//a
		playerLook[1][0] = '-';
		if(attackCounter ==0){
			mapDraw->editBorder(xposition-1, yposition+2, '6');
			mapDraw->editBorder(xposition-2, yposition+1, '6');
			mapDraw->editBorder(xposition-2, yposition, '6');
			mapDraw->editBorder(xposition-2, yposition-1, '6');
			mapDraw->editBorder(xposition-1, yposition-2, '6');
		}
		attackCounter++;
		switch(attackCounter){
			case 1:
				mapDraw->drawChar(xposition-1, yposition+2, '/');
			break;
			case 2:
				mapDraw->drawChar(xposition-2, yposition+1, '-');
			break;
			case 3:
				mapDraw->drawChar(xposition-2, yposition, '-');
			break;
			case 4:
				mapDraw->drawChar(xposition-2, yposition-1, '-');
			break;
			case 5:
				mapDraw->drawChar(xposition-1, yposition-2, '\\');
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
			mapDraw->editBorder(xposition+1, yposition-2, '6');
			mapDraw->editBorder(xposition+2, yposition-1, '6');
			mapDraw->editBorder(xposition+2, yposition, '6');
			mapDraw->editBorder(xposition+2, yposition+1, '6');
			mapDraw->editBorder(xposition+1, yposition+2, '6');
		}
		attackCounter++;
		switch(attackCounter){
			case 1:
				mapDraw->drawChar(xposition+1, yposition-2, '/');
			break;
			case 2:
				mapDraw->drawChar(xposition+2, yposition-1, '-');
			break;
			case 3:
				mapDraw->drawChar(xposition+2, yposition, '-');
			break;
			case 4:
				mapDraw->drawChar(xposition+2, yposition+1, '-');
			break;
			case 5:
				mapDraw->drawChar(xposition+1, yposition+2, '\\');
			break;
			case 6:
				attackCounter = 0;
				mapDraw->restoreBorder();
				playerLook[1][2] = '\\';
			break;
		}
	}else if(direction == 3){//w
		if(attackCounter ==0){
			mapDraw->editBorder(xposition-2, yposition-1, '6');
			mapDraw->editBorder(xposition-1, yposition-2, '6');
			mapDraw->editBorder(xposition, yposition-2, '6');
			mapDraw->editBorder(xposition+1, yposition-2, '6');
			mapDraw->editBorder(xposition+2, yposition-1, '6');
		}
		attackCounter++;
		switch(attackCounter){
			case 1:
				mapDraw->drawChar(xposition-2, yposition-1, '\\');
			break;
			case 2:
				mapDraw->drawChar(xposition-1, yposition-2, '\\');
			break;
			case 3:
				mapDraw->drawChar(xposition, yposition-2, '|');
			break;
			case 4:
				mapDraw->drawChar(xposition+1, yposition-2, '/');
			break;
			case 5:
				mapDraw->drawChar(xposition+2, yposition-1, '/');
			break;
			case 6:
				attackCounter = 0;
				mapDraw->restoreBorder();
			break;
		}
	}else if(direction == 4){//s
		if(attackCounter ==0){
			mapDraw->editBorder(xposition+2, yposition+1, '6');
			mapDraw->editBorder(xposition+1, yposition+2, '6');
			mapDraw->editBorder(xposition, yposition+2, '6');
			mapDraw->editBorder(xposition-1, yposition+2, '6');
			mapDraw->editBorder(xposition-2, yposition+1, '6');
		}
		attackCounter++;
		switch(attackCounter){
			case 1:
				mapDraw->drawChar(xposition+2, yposition+1, '\\');
			break;
			case 2:
				mapDraw->drawChar(xposition+1, yposition+2, '\\');
			break;
			case 3:
				mapDraw->drawChar(xposition, yposition+2, '|');
			break;
			case 4:
				mapDraw->drawChar(xposition-1, yposition+2, '/');
			break;
			case 5:
				mapDraw->drawChar(xposition-2, yposition+1, '/');
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
				mapDraw->drawChar(xposition-1, yposition-2, 'c');
				mapDraw->drawChar(xposition, yposition-2, 'c');
				mapDraw->drawChar(xposition+1, yposition-2, 'c');
				mapDraw->drawChar(xposition-1, yposition+2, 'c');
				mapDraw->drawChar(xposition, yposition+2, 'c');
				mapDraw->drawChar(xposition+1, yposition+2, 'c');
				mapDraw->drawChar(xposition+2, yposition-1, 'c');
				mapDraw->drawChar(xposition+2, yposition, 'c');
				mapDraw->drawChar(xposition+2, yposition+1, 'c');
				mapDraw->drawChar(xposition-2, yposition-1, 'c');
				mapDraw->drawChar(xposition-2, yposition, 'c');
				mapDraw->drawChar(xposition-2, yposition+1, 'c');
			break;
			case 2:
				mapDraw->drawChar(xposition-1, yposition-2, 'c');
				mapDraw->drawChar(xposition, yposition-2, 'c');
				mapDraw->drawChar(xposition+1, yposition-2, 'c');
				mapDraw->drawChar(xposition-1, yposition+2, 'c');
				mapDraw->drawChar(xposition, yposition+2, 'c');
				mapDraw->drawChar(xposition+1, yposition+2, 'c');
				mapDraw->drawChar(xposition+2, yposition-1, 'c');
				mapDraw->drawChar(xposition+2, yposition, 'c');
				mapDraw->drawChar(xposition+2, yposition+1, 'c');
				mapDraw->drawChar(xposition-2, yposition-1, 'c');
				mapDraw->drawChar(xposition-2, yposition, 'c');
				mapDraw->drawChar(xposition-2, yposition+1, 'c');
				mapDraw->drawChar(xposition-1, yposition-3, 'c');
				mapDraw->drawChar(xposition, yposition-3, 'c');
				mapDraw->drawChar(xposition+1, yposition-3, 'c');
				mapDraw->drawChar(xposition+2, yposition-2, 'c');
				mapDraw->drawChar(xposition-1, yposition+3, 'c');
				mapDraw->drawChar(xposition, yposition+3, 'c');
				mapDraw->drawChar(xposition+1, yposition+3, 'c');
				mapDraw->drawChar(xposition+2, yposition+2, 'c');
				mapDraw->drawChar(xposition+3, yposition-1, 'c');
				mapDraw->drawChar(xposition+3, yposition, 'c');
				mapDraw->drawChar(xposition+3, yposition+1, 'c');
				mapDraw->drawChar(xposition-2, yposition+2, 'c');
				mapDraw->drawChar(xposition-3, yposition-1, 'c');
				mapDraw->drawChar(xposition-3, yposition, 'c');
				mapDraw->drawChar(xposition-3, yposition+1, 'c');
				mapDraw->drawChar(xposition-2, yposition-2, 'c');
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
