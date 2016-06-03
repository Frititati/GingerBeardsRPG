/*
 * Mob.cpp
 *
 *  Created on: 7 May 2016
 *      Author: Filippo M Cardano
 */

#include "Mob.h"
#include "Map.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

Player* playerposition;

Mob::Mob() {
	hp = 17;
	attackStrength = 15;
	speedCount = 0;
	xposition = 10;
	yposition = 10;
	speed = 5;
	viewDistance = 400;
	aggressive = true;
	defenceLoot = 0;
	attackLoot = 0;
	healthLoot = 0;
	healthAddLoot = 0;
	maxPowerAddLoot = 0;
	width = 0;
	height = 0;
}

void Mob::createBoss(int x, int y) {
	string line;
	ifstream myfile("boss.txt");
	mobLook = new char *[BOSS_HEIGHT];
	for (int i = 0; i < BOSS_HEIGHT; i++) {
		mobLook[i] = new char[BOSS_WIDTH];
	}
	if (myfile.is_open()) {
		for (int i = 0; i < BOSS_HEIGHT && getline(myfile, line); i++) {
			for (unsigned int j = 0; j < BOSS_WIDTH; j++) {
				char c = line.at(j);
				if (c == ' ') {
					c = EMPTY;
				}
				mobLook[i][j] = c;
			}
		}
		myfile.close();
		// boss' stats
		xposition = x;
		yposition = y;
		width = BOSS_WIDTH;
		height = BOSS_HEIGHT;
		hp = 100;
		attackStrength = 9;
		speed = 3;
		viewDistance = 400;
		healthLoot = 2000;
	} else {
		cout << "Unable to open file" << endl;
	}
}

void Mob::creatingMob(int x, int y, Player*& player) {
	mobLook = new char *[MOB_HEIGHT];
	mobLook[0] = new char[MOB_WIDTH];
	mobLook[0][0] = 'G';
	mobLook[0][1] = 'O';
	mobLook[0][2] = 'B';
	width = MOB_WIDTH;
	height = MOB_HEIGHT;
	hp = 17;
	attackStrength = 15;
	speedCount = 0;
	xposition = 10;
	yposition = 10;
	speed = 5;
	viewDistance = 400;
	aggressive = true;
	defenceLoot = 0;
	attackLoot = 0;
	healthLoot = 0;
	healthAddLoot = 0;

	int difficulty;
	difficulty = (player->getDefense() * 3);
	difficulty += (player->getAttackStrength() * 10);
	difficulty += (player->getMaxHP() / 2);
	difficulty = difficulty / 3;
	speedCount = 0;
	int type = RTD(1, 100);
	if (type < 50) { // imp gob
		int monster = RTD(1, 2);
		setLook(monster);
		setStats(difficulty, monster, player);
	} else if (type < 75) { // vam and zom
		int monster = RTD(3, 4);
		setLook(monster);
		setStats(difficulty, monster, player);
	} else if (type < 95) { //ang
		setLook(5);
		setStats(difficulty, 5, player);
	} else { // god
		setLook(6);
		setStats(difficulty, 6, player);
	}
	xposition = x;
	yposition = y;
}
void Mob::setStats(int difficulty, int monster, Player*& playerLoot) {
	switch (monster) {
	case 1: //gob
		hp = difficulty / 10;
		attackStrength = difficulty / 15;
		speed = 10;
		viewDistance = 500; // sqrt(10)
		healthLoot = playerLoot->getHP() / 12;
		break;
	case 2: //imp
		hp = difficulty / 20;
		attackStrength = difficulty / 20;
		speed = 2;
		viewDistance = 300;
		healthLoot = playerLoot->getHP() / 16;
		break;
	case 3: //vam
		hp = difficulty / 10;
		attackStrength = difficulty / 15;
		speed = 4;
		viewDistance = 500; // sqrt(10)
		if (RTD(1, 2) == 1) {
			attackLoot = 2;
		} else {
			attackLoot = 4;
		}
		break;
	case 4: //zom
		hp = difficulty / 5;
		attackStrength = difficulty / 8; //difficulty->getHP()/20;
		speed = 12;
		viewDistance = 400;
		healthLoot = difficulty / 16;
		if (RTD(1, 2) == 1) {
			defenceLoot = 2;
		} else {
			defenceLoot = 4;
		}
		break;
	case 5: //spi
		hp = difficulty / 4;
		attackStrength = difficulty / 8; // difficulty->getHP()/15;
		speed = 4;
		viewDistance = 1000; // sqrt(10)
		healthLoot = difficulty / 12;
		if (RTD(1, 2) == 1) {
			healthAddLoot = 10;
		} else {
			healthAddLoot = 20;
		}
		break;
	case 6: //lic
		hp = difficulty;
		attackStrength = difficulty / 5; //difficulty->getHP()/20;
		speed = 7;
		viewDistance = 1000;
		healthLoot = difficulty / 2;
		healthAddLoot = playerLoot->getMaxHP() / 20;
		attackLoot = 6;
		int bonusPower = RTD(1, 100);
		if (bonusPower < 16) {
			maxPowerAddLoot = 1;
		}
		break;
	}
	int bonus = RTD(1, 100);
	if (bonus > 98) {
		attackLoot = attackLoot + 5;
		defenceLoot = defenceLoot + 5;
		healthAddLoot = healthAddLoot + 25;
		maxPowerAddLoot += 1;
		healthLoot = 1000;
	}
}

int Mob::getPowerAddLoot() {
	return maxPowerAddLoot;
}
//void Mob::setStats(Player*& difficulty, int monster){
//	switch(monster){
//	case 1:
//		hp = difficulty->getHP()/15;
//		attackStrength = 0;// difficulty->getHP()/15;
//		speed = 10;
//		viewDistance = 500; // sqrt(10)
//		healthLoot = difficulty->getHP()/12;
//	break;
//	case 2:
//		hp = difficulty->getHP()/20;
//		attackStrength = 0;//difficulty->getHP()/20;
//		speed = 3;
//		viewDistance = 300;
//		healthLoot = difficulty->getHP()/16;
//	break;
//	case 3:
//		hp = difficulty->getHP()/15;
//		attackStrength = 0;// difficulty->getHP()/15;
//		speed = 10;
//		viewDistance = 500; // sqrt(10)
//		healthLoot = difficulty->getHP()/12;
//		if(RTD(1,2) == 1){
//			attackLoot = difficulty->getAttackStrength()/10;
//		}else{
//			attackLoot = difficulty->getAttackStrength()/20;
//		}
//	break;
//	case 4:
//		hp = difficulty->getHP()/20;
//		attackStrength = 0;//difficulty->getHP()/20;
//		speed = 3;
//		viewDistance = 300;
//		healthLoot = difficulty->getHP()/16;
//	break;
//	case 5:
//		hp = difficulty->getHP()/15;
//		attackStrength = 0;// difficulty->getHP()/15;
//		speed = 10;
//		viewDistance = 500; // sqrt(10)
//		healthLoot = difficulty->getHP()/12;
//	break;
//	case 6:
//		hp = difficulty->getHP()/20;
//		attackStrength = 0;//difficulty->getHP()/20;
//		speed = 3;
//		viewDistance = 300;
//		healthLoot = difficulty->getHP()/16;
//	break;
//	}
//}

void Mob::setLook(int whichone) {
	switch (whichone) {
	case 1:
		mobLook[0][0] = 'G';
		mobLook[0][1] = 'O';
		mobLook[0][2] = 'B';
		break;
	case 2:
		mobLook[0][0] = 'I';
		mobLook[0][1] = 'M';
		mobLook[0][2] = 'P';
		break;
	case 3:
		mobLook[0][0] = 'V';
		mobLook[0][1] = 'A';
		mobLook[0][2] = 'M';
		break;
	case 4:
		mobLook[0][0] = 'Z';
		mobLook[0][1] = 'O';
		mobLook[0][2] = 'M';
		break;
	case 5:
		mobLook[0][0] = 'S';
		mobLook[0][1] = 'P';
		mobLook[0][2] = 'I';
		break;
	case 6:
		mobLook[0][0] = 'L';
		mobLook[0][1] = 'I';
		mobLook[0][2] = 'C';
		break;
	}
}

int Mob::RTD(int from, int to) {
	return rand() % (to - from + 1) + from;
}

void Mob::mobMovement(Map*& mapEditor, Player*& xyPlayer) {
	playerposition = xyPlayer;
	int tempx = xposition;
	int tempy = yposition;
	int playerx;
	int playery;
	playerposition->playerPosition(&playerx, &playery);
	differencex = abs(xposition - playerx) - width / 2 - PLAYER_WIDTH / 2 - 1;
	differencey = abs(yposition - playery) - height / 2 - PLAYER_HEIGHT / 2 - 1;
	if ((speedCount % speed) == 0) {
		if (aggressive
				&& (pow(differencex, 2) + pow(differencey, 2)) < viewDistance) {
			if (differencey < 1 && differencex < 1) {
				aggressive = playerposition->damage(attackStrength);
			} else if (differencey < differencex) {
				if (xposition < playerx) {
					xposition++;
				} else {
					xposition--;
				}
			} else {
				if (yposition < playery) {
					yposition++;
				} else {
					yposition--;
				}
			}
		} else {
			int randomMovement = rand() % 100;
			if (randomMovement < 50) {
				if (randomMovement < 25) {
					xposition++;
				} else {
					xposition--;
				}
			} else {
				if (randomMovement < 75) {
					yposition++;
				} else {
					yposition--;
				}
			}
		}
		cout << "Mob::mobMovement1" << endl;
		const int LIMIT = 1000; // avoid a bad crash if the mob cannot move
		for (int i = 0;
				i < LIMIT
						&& !mapEditor->testBorder(xposition, yposition, width,
								height, mobLook); i++) {
			cout << "Mob::mobMovement2" << endl;
			xposition = tempx;
			yposition = tempy;
			int randomMovement = rand() % 100;
			if (randomMovement < 50) {
				if (randomMovement < 25) {
					xposition++;
				} else {
					xposition--;
				}
			} else {
				if (randomMovement < 75) {
					yposition++;
				} else {
					yposition--;
				}
			}
		}
	}
	cout << "Mob::mobMovement3" << endl;
	mapEditor->drawCharacter(xposition, yposition, width, height, mobLook);
	cout << "Mob::mobMovement4" << endl;
//	if((pow(differencex, 2)+ pow(differencey,2)) < viewDistance){
	detectDamage(mapEditor);
	cout << "Mob::mobMovement5" << endl;
//	}
	speedCount++;
}

void Mob::detectDamage(Map*& mapChecker) {
	for (int i = yposition - height / 2, looki = 0; looki < height; i++, looki++) {
		for (int j = xposition - width / 2, lookj = 0; lookj < width; j++, lookj++) {
			if (mobLook[looki][lookj] != EMPTY) {
				char damageIndicator = mapChecker->getBorderCell(j, i);
				if ((damageIndicator != '0') && ((speedCount % 6) == 0)) { //we do this to test if he is getting hit and to make sure he doesn't get hit 100 times
					switch (damageIndicator) {
					case '6': // sword swing
						hp -= playerposition->getAttackStrength();
						return;
					case '7': // aoe
						hp -= playerposition->getAOEDamage();
						return;
					case '8':
						return;
					case '9':
						return;
					}
				}
			}
		}
	}
}

bool Mob::despawnCheck() {
	if ((pow(differencex, 2) + pow(differencey, 2)) > 3600) {
		return true;
	}
	return false;
}

int Mob::getHealth() {
	return hp;
}

int Mob::getHealthLoot() {
	return healthLoot;
}

int Mob::getDefenceLoot() {
	return defenceLoot;
}

int Mob::getAttackLoot() {
	return attackLoot;
}
int Mob::getHealthAddLoot() {
	return healthAddLoot;
}
Mob::~Mob() {
}

