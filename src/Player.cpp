#include "Player.h"
#include "GingerBeards.h"
#include <windows.h>
#include <iostream>
using namespace std;

char** playerLook;
Map* mapDraw;

bool isDead;
bool chargePower;

Player::Player() {
	isDead = false;
	chargePower = true;
	playerLook = new char *[PLAYER_HEIGHT];
	for (int i = 0; i < PLAYER_HEIGHT; i++) {
		playerLook[i] = new char[PLAYER_WIDTH];
	}
//	(°_ʖ°)
//	EMPTY o EMPTY
	playerLook[0][0] = '^';
	playerLook[0][1] = '_';
	playerLook[0][2] = '^';
	this->standardLook();
	xposition = 396;
	yposition = 162;
	attackCounter = 0;
	attackDir = 8;
	maxHP = 600;
	HP = 500;
	power = 3;
	maxPower = 6;
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

	if (!mapEditor->testBorder(xposition, yposition, PLAYER_WIDTH,
			PLAYER_HEIGHT, playerLook)) {
		xposition = tempx;
		yposition = tempy;
	}
}

void Player::heal() {
	if (healDelaySec <= 0) {
		if (!isDead) {
			HP = min(maxHP, HP + healPerSec);
		}
	} else {
		healDelaySec--;
	}
}

bool Player::hasDied() {
	return isDead;
}

int Player::getAOEDamage() {
	return aoeDamage;
}

// true if the player still lives
bool Player::damage(int amount) {
	int damage = amount <= defense ? 1 : amount - defense;
	HP -= damage;
	healDelaySec = 2 * 1000 / GAME_DELAY_MS;
	if (HP <= 0) {
		this->standardLook();
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
	attack(attackDir);
	mapEditor->drawCharacter(xposition, yposition, PLAYER_WIDTH, PLAYER_HEIGHT,
			playerLook);
}
void Player::setAttack(int direction) {
	if (attackCounter == 0) {
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
	if (max <= amount) {
		this->HP = maxHP;
	} else {
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

void Player::setMaxHP(int amount) {
	this->maxHP = amount;
}

void Player::teleport(int x, int y) {
	xposition = x;
	yposition = y;
}

void Player::leftSwing() {
	attackCounter = (attackCounter + 1) % 6;
	playerLook[0][0] = '<';
	playerLook[0][1] = '_';
	playerLook[0][2] = '<';
	switch (attackCounter) {
	case 1:
		playerLook[1][0] = INVISIBLE;
		mapDraw->drawChar(xposition - 1, yposition + 2, '\\', PLAYER_SWING);
		mapDraw->drawChar(xposition - 2, yposition + 3, '/', PLAYER_SWING);
		break;
	case 2:
		mapDraw->drawChar(xposition - 2, yposition + 1, '|', PLAYER_SWING);
		mapDraw->drawChar(xposition - 4, yposition + 2, '/', PLAYER_SWING);
		break;
	case 3:
		playerLook[1][0] = '-';
		mapDraw->drawChar(xposition - 2, yposition, '-', PLAYER_SWING);
		mapDraw->drawChar(xposition - 3, yposition, '|', PLAYER_SWING);
		mapDraw->drawChar(xposition - 4, yposition, '-', PLAYER_SWING);
		mapDraw->drawChar(xposition - 5, yposition, '-', PLAYER_SWING);
		break;
	case 4:
		playerLook[1][0] = INVISIBLE;
		mapDraw->drawChar(xposition - 2, yposition - 1, '|', PLAYER_SWING);
		mapDraw->drawChar(xposition - 4, yposition - 2, '\\', PLAYER_SWING);
		break;
	case 5:
		mapDraw->drawChar(xposition - 1, yposition - 2, '/', PLAYER_SWING);
		mapDraw->drawChar(xposition - 2, yposition - 3, '\\', PLAYER_SWING);
	}
}
void Player::rightSwing() {
	attackCounter = (attackCounter + 1) % 6;
	playerLook[0][0] = '>';
	playerLook[0][1] = '_';
	playerLook[0][2] = '>';
	switch (attackCounter) {
	case 1:
		playerLook[1][2] = INVISIBLE;
		mapDraw->drawChar(xposition + 1, yposition + 2, '/', PLAYER_SWING);
		mapDraw->drawChar(xposition + 2, yposition + 3, '\\', PLAYER_SWING);
		break;
	case 2:
		mapDraw->drawChar(xposition + 2, yposition + 1, '|', PLAYER_SWING);
		mapDraw->drawChar(xposition + 4, yposition + 2, '\\', PLAYER_SWING);
		break;
	case 3:
		playerLook[1][2] = '-';
		mapDraw->drawChar(xposition + 2, yposition, '-', PLAYER_SWING);
		mapDraw->drawChar(xposition + 3, yposition, '|', PLAYER_SWING);
		mapDraw->drawChar(xposition + 4, yposition, '-', PLAYER_SWING);
		mapDraw->drawChar(xposition + 5, yposition, '-', PLAYER_SWING);
		break;
	case 4:
		playerLook[1][2] = INVISIBLE;
		mapDraw->drawChar(xposition + 2, yposition - 1, '|', PLAYER_SWING);
		mapDraw->drawChar(xposition + 4, yposition - 2, '/', PLAYER_SWING);
		break;
	case 5:
		mapDraw->drawChar(xposition + 1, yposition - 2, '\\', PLAYER_SWING);
		mapDraw->drawChar(xposition + 2, yposition - 3, '/', PLAYER_SWING);
	}
}
void Player::frontSwing() {
	attackCounter = (attackCounter + 1) % 6;
	playerLook[0][0] = '>';
	playerLook[0][1] = '_';
	playerLook[0][2] = '<';
	switch (attackCounter) {
	case 1:
		playerLook[1][2] = INVISIBLE;
		mapDraw->drawChar(xposition - 2, yposition - 1, '/', PLAYER_SWING);
		mapDraw->drawChar(xposition - 3, yposition - 2, '\\', PLAYER_SWING);
		break;
	case 2:
		mapDraw->drawChar(xposition - 1, yposition - 2, '/', PLAYER_SWING);
		mapDraw->drawChar(xposition - 2, yposition - 3, '\\', PLAYER_SWING);
		break;
	case 3:
		//			mapDraw->drawChar(xposition, yposition - 4, '|', PLAYER_SWING);
		mapDraw->drawChar(xposition, yposition - 3, '|', PLAYER_SWING);
		mapDraw->drawChar(xposition, yposition - 2, 'T', PLAYER_SWING);
		break;
	case 4:
		mapDraw->drawChar(xposition + 1, yposition - 2, '\\', PLAYER_SWING);
		mapDraw->drawChar(xposition + 2, yposition - 3, '/', PLAYER_SWING);
		break;
	case 5:
		mapDraw->drawChar(xposition + 2, yposition - 1, '\\', PLAYER_SWING);
		mapDraw->drawChar(xposition + 3, yposition - 2, '/', PLAYER_SWING);
	}
}
void Player::backSwing() {
	attackCounter = (attackCounter + 1) % 6;
	mapDraw->restoreBorder();
	playerLook[0][0] = '>';
	playerLook[0][1] = '_';
	playerLook[0][2] = '<';
	switch (attackCounter) {
	case 1:
		playerLook[1][0] = '\\';
		mapDraw->drawChar(xposition + 2, yposition + 1, '/', PLAYER_SWING);
		mapDraw->drawChar(xposition + 3, yposition + 2, '\\', PLAYER_SWING);
		break;
	case 2:
		mapDraw->drawChar(xposition + 1, yposition + 2, '/', PLAYER_SWING);
		mapDraw->drawChar(xposition + 2, yposition + 3, '\\', PLAYER_SWING);
		break;
	case 3:
		playerLook[1][0] = '|';
		mapDraw->drawChar(xposition, yposition + 2, '|', PLAYER_SWING);
		mapDraw->drawChar(xposition, yposition + 3, 'T', PLAYER_SWING);
		//			mapDraw->drawChar(xposition, yposition + 4, '|', PLAYER_SWING);
		break;
	case 4:
		playerLook[1][0] = '/';
		mapDraw->drawChar(xposition - 1, yposition + 2, '\\', PLAYER_SWING);
		mapDraw->drawChar(xposition - 2, yposition + 3, '-', PLAYER_SWING);
		break;
	case 5:
		mapDraw->drawChar(xposition - 2, yposition + 1, '\\', PLAYER_SWING);
		mapDraw->drawChar(xposition - 3, yposition + 2, '/', PLAYER_SWING);
	}
}

// hard coded
void Player::attack(int direction) {
	if (isDead)
		return;
	if (direction == 1) { //a
		leftSwing();
	} else if (direction == 2) { //d
		rightSwing();
	} else if (direction == 3) { //w
		frontSwing();
	} else if (direction == 4) { //s
		backSwing();
	} else if (direction == 5) { //aoe f1
		AOEAttack();
	}
	if (attackCounter == 0) {
		attackDir = 0;
		mapDraw->restoreBorder();
		this->standardLook();
		chargePower = true;
	}
}

int Player::getPower() {
	return power;
}

void Player::increasePower() {
	if (chargePower) {
		power = min(power + 1, maxPower);
	}
}

int Player::getMaxPower() {
	return maxPower;
}

void Player::AOEAttack() {
	if (attackCounter == 0) {
		if (power >= MINIMUM_AOE_COST) {
			chargePower = false;	// avoid that the player overuses the special ability
			playerLook[2][1] = AOE_CHAR;
			aoeDamage = (int) attackStrength * (0.5 + 0.1 * power);
			power = 0;
			attackCounter = (attackCounter + 1) % AOE_RADIUS;
		}
	} else {
		attackCounter = (attackCounter + 1) % AOE_RADIUS;
	}
	int topLeftX = xposition - PLAYER_WIDTH / 2;
	int topLeftY = yposition - PLAYER_HEIGHT / 2;
	int bottomRightX = xposition + PLAYER_WIDTH / 2;
	int bottomRightY = yposition + PLAYER_HEIGHT / 2;
	for (int i = 1; i <= attackCounter; i++) {
		int x = topLeftX;
		int y = topLeftY - i;
		// draw north edge
		for (int j = 0; j < PLAYER_WIDTH; j++) {
			mapDraw->drawChar(x++, y, AOE_CHAR, AOE_CODE);
		}
		y++;
		// draw north east diagonal
		while (y < topLeftY) {
			mapDraw->drawChar(x++, y++, AOE_CHAR, AOE_CODE);
		}
		// draw east edge
		for (int j = 0; j < PLAYER_HEIGHT; j++) {
			mapDraw->drawChar(x, y++, AOE_CHAR, AOE_CODE);
		}
		x--;
		// draw south east diagonal
		while (x > bottomRightX) {
			mapDraw->drawChar(x--, y++, AOE_CHAR, AOE_CODE);
		}
		// draw south edge
		for (int j = 0; j < PLAYER_WIDTH; j++) {
			mapDraw->drawChar(x--, y, AOE_CHAR, AOE_CODE);
		}
		y--;
		// draw south west diagonal
		while (y > bottomRightY) {
			mapDraw->drawChar(x--, y--, AOE_CHAR, AOE_CODE);
		}
		// draw west edge
		for (int j = 0; j < PLAYER_HEIGHT; j++) {
			mapDraw->drawChar(x, y--, AOE_CHAR, AOE_CODE);
		}
		x++;
		// draw north west diagonal
		while (x < topLeftX) {
			mapDraw->drawChar(x++, y--, AOE_CHAR, AOE_CODE);
		}
	}
}
//		switch (attackCounter) {
//		case 1:
//			mapDraw->drawChar(xposition - 1, yposition - 2, 'c', AOE);
//			mapDraw->drawChar(xposition, yposition - 2, 'c', AOE);
//			mapDraw->drawChar(xposition + 1, yposition - 2, 'c', AOE);
//			mapDraw->drawChar(xposition - 1, yposition + 2, 'c', AOE);
//			mapDraw->drawChar(xposition, yposition + 2, 'c', AOE);
//			mapDraw->drawChar(xposition + 1, yposition + 2, 'c', AOE);
//			mapDraw->drawChar(xposition + 2, yposition - 1, 'c', AOE);
//			mapDraw->drawChar(xposition + 2, yposition, 'c', AOE);
//			mapDraw->drawChar(xposition + 2, yposition + 1, 'c', AOE);
//			mapDraw->drawChar(xposition - 2, yposition - 1, 'c', AOE);
//			mapDraw->drawChar(xposition - 2, yposition, 'c', AOE);
//			mapDraw->drawChar(xposition - 2, yposition + 1, 'c', AOE);
//			break;
//		case 2:
//			mapDraw->drawChar(xposition - 1, yposition - 2, 'c', AOE);
//			mapDraw->drawChar(xposition, yposition - 2, 'c', AOE);
//			mapDraw->drawChar(xposition + 1, yposition - 2, 'c', AOE);
//			mapDraw->drawChar(xposition - 1, yposition + 2, 'c', AOE);
//			mapDraw->drawChar(xposition, yposition + 2, 'c', AOE);
//			mapDraw->drawChar(xposition + 1, yposition + 2, 'c', AOE);
//			mapDraw->drawChar(xposition + 2, yposition - 1, 'c', AOE);
//			mapDraw->drawChar(xposition + 2, yposition, 'c', AOE);
//			mapDraw->drawChar(xposition + 2, yposition + 1, 'c', AOE);
//			mapDraw->drawChar(xposition - 2, yposition - 1, 'c', AOE);
//			mapDraw->drawChar(xposition - 2, yposition, 'c', AOE);
//			mapDraw->drawChar(xposition - 2, yposition + 1, 'c', AOE);
//
//			mapDraw->drawChar(xposition - 1, yposition - 3, 'c', AOE);
//			mapDraw->drawChar(xposition, yposition - 3, 'c', AOE);
//			mapDraw->drawChar(xposition + 1, yposition - 3, 'c', AOE);
//
//			mapDraw->drawChar(xposition + 2, yposition - 2, 'c', AOE);
//			mapDraw->drawChar(xposition - 1, yposition + 3, 'c', AOE);
//			mapDraw->drawChar(xposition, yposition + 3, 'c', AOE);
//			mapDraw->drawChar(xposition + 1, yposition + 3, 'c', AOE);
//			mapDraw->drawChar(xposition + 2, yposition + 2, 'c', AOE);
//			mapDraw->drawChar(xposition + 3, yposition - 1, 'c', AOE);
//			mapDraw->drawChar(xposition + 3, yposition, 'c', AOE);
//			mapDraw->drawChar(xposition + 3, yposition + 1, 'c', AOE);
//			mapDraw->drawChar(xposition - 2, yposition + 2, 'c', AOE);
//			mapDraw->drawChar(xposition - 3, yposition - 1, 'c', AOE);
//			mapDraw->drawChar(xposition - 3, yposition, 'c', AOE);
//			mapDraw->drawChar(xposition - 3, yposition + 1, 'c', AOE);
//			mapDraw->drawChar(xposition - 2, yposition - 2, 'c', AOE);
//			break;
//		case 3:
//			//mapDraw->drawChar(xpossition, ypossition+2, '|');
//			break;
//		case 4:
//			//mapDraw->drawChar(xpossition-1, ypossition+2, '/');
//			break;
//		case 5:
//			//mapDraw->drawChar(xpossition-2, ypossition+1, '/');
//			break;
//		case 6:
//			attackCounter = 0;
//			break;
//		}
//	}

void Player::loadCharacter(int x, int y, int attack, int def, int hp,
		int maxhp, int pow, int maxPow) {
	this->xposition = x;
	this->yposition = y;
	this->attackStrength = attack;
	this->defense = def;
	this->HP = hp;
	this->maxHP = maxhp;
	this->power = pow;
	this->maxPower = maxPow;
}

void Player::addMaxPower(int amount) {
	maxPower = min(POWER_CAP, maxPower + amount);
}

void Player::standardLook() {
	playerLook[1][0] = '/';
	playerLook[1][1] = '|';
	playerLook[1][2] = '\\';
	playerLook[2][0] = '/';
	playerLook[2][1] = EMPTY;
	playerLook[2][2] = '\\';
}
