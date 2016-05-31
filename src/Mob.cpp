/*
 * Mob.cpp
 *
 *  Created on: 7 May 2016
 *      Author: Filippo M Cardano
 */

#include "Mob.h"
#include "map.h"
#include "stdlib.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

Player* playerposition;

Mob::Mob(){
//	mobLook = new char *[MOB_HEIGHT];
	mobLook = new char *[MOB_HEIGHT];
	mobLook[0] = new char[MOB_WIDTH];
	mobLook[0][0] = 'G';
	mobLook[0][1] = 'O';
	mobLook[0][2] = 'B';
	hp = 17;
	attackStrength = 15;
	speedCount = 0;
	xpossition = 10;
	ypossition = 10;
	speed = 5;
	viewDistance = 400;
	aggressive = true;
	defenceLoot = 0;
	attackLoot = 0;
	healthLoot = 0;
	healthAddLoot = 0;
}

void Mob::creatingMob(int x, int y, Player*& player) {
	mobLook = new char *[MOB_HEIGHT];
	mobLook[0] = new char[MOB_WIDTH];
	mobLook[0][0] = 'G';
	mobLook[0][1] = 'O';
	mobLook[0][2] = 'B';
	hp = 17;
	attackStrength = 15;
	speedCount = 0;
	xpossition = 10;
	ypossition = 10;
	speed = 5;
	viewDistance = 400;
	aggressive = true;
	defenceLoot = 0;
	attackLoot = 0;
	healthLoot = 0;
	healthAddLoot = 0;
	int difficulty;
	difficulty = player->getDefense();
	difficulty =+ (player->getAttackStrength()*2);
	difficulty =+ (player->getMaxHP()/3);
	difficulty = difficulty/3;
	speedCount = 0;
	int type = RTD(1,100);
	if(type < 50){ // imp gob
		int monster = RTD(1,2);
		setLook(monster);
		setStats(difficulty, monster , player);
	}
	else if(type < 75){ // vam and zom
		int monster = RTD(3,4);
		setLook(monster);
		setStats(difficulty, monster, player);
	}else if (type < 95){ //ang
		setLook(5);
		setStats(difficulty, 5, player);
	}else{ // god
		setLook(6);
		setStats(difficulty, 6, player);
	}
	xpossition = x;
	ypossition = y;
}
void Mob::setStats(int difficulty, int monster, Player*& playerLoot){
	switch(monster){
	case 1: //gob
		hp = difficulty/10;
		attackStrength = difficulty/15;
		speed = 10;
		viewDistance = 500; // sqrt(10)
		healthLoot = playerLoot->getHP()/12;
	break;
	case 2: //imp
		hp = difficulty/20;
		attackStrength = difficulty/20;
		speed = 2;
		viewDistance = 300;
		healthLoot = playerLoot->getHP()/16;
	break;
	case 3: //vam
		hp = difficulty/10;
		attackStrength = difficulty/15;
		speed = 4;
		viewDistance = 500; // sqrt(10)
		if(RTD(1,2) == 1){
			attackLoot = 2;
		}else{
			attackLoot = 4;
		}
	break;
	case 4: //zom
		hp = difficulty/5;
		attackStrength = difficulty/8;//difficulty->getHP()/20;
		speed = 12;
		viewDistance = 400;
		healthLoot = difficulty/16;
		if(RTD(1,2) == 1){
			defenceLoot = 2;
		}else{
			defenceLoot = 4;
		}
	break;
	case 5: //ang
		hp = difficulty/4;
		attackStrength = difficulty/8;// difficulty->getHP()/15;
		speed = 4;
		viewDistance = 1000; // sqrt(10)
		healthLoot = difficulty/12;
		if(RTD(1,2) == 1){
			healthAddLoot = 10;
		}else{
			healthAddLoot = 20;
		}
	break;
	case 6: //god
		hp = difficulty;
		attackStrength = difficulty/5;//difficulty->getHP()/20;
		speed = 7;
		viewDistance = 1000;
		healthLoot = difficulty/2;
		healthAddLoot = playerLoot->getMaxHP()/20;
		attackLoot = 6;
	break;
	}
	int bonus = RTD(1,100);
	if(bonus > 98){
		attackLoot = attackLoot + 5;
		defenceLoot = defenceLoot + 5;
		healthAddLoot = healthAddLoot + 25;
		healthLoot = 1000;
	}
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

void Mob::setLook(int whichone){
	switch(whichone){
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
			mobLook[0][0] = 'A';
			mobLook[0][1] = 'N';
			mobLook[0][2] = 'G';
		break;
		case 6:
			mobLook[0][0] = 'G';
			mobLook[0][1] = 'O';
			mobLook[0][2] = 'D';
		break;
	}
}

int Mob::RTD(int from, int to){
	return rand() % (to - from + 1) + from;
}

void Mob::mobMovement(Map*& mapEditor, Player*& xyPlayer){
	playerposition = xyPlayer;
	int tempx = xpossition;
	int tempy = ypossition;
	int playerx;
	int playery;
	playerposition->playerPosition(&playerx, &playery);
	differencex = abs(xpossition - playerx);
	differencey = abs(ypossition - playery);
	if((speedCount % speed) == 0){
		if(aggressive && (pow(differencex, 2)+ pow(differencey,2)) < viewDistance){
			if(differencey < 3 && differencex < 4){
				aggressive = playerposition->damage(attackStrength);
				goto nomovement;
			}
			if(differencey < differencex){
				if(xpossition < playerx){
					xpossition++;
				}else{
					xpossition--;
				}
			}else{
				if(ypossition < playery){
					ypossition++;
				}else{
					ypossition--;
				}
			}
		}else{
			int randomMovement = rand() %100;
			if(randomMovement < 50){
				if(randomMovement < 25){
					xpossition++;
				}else{
					xpossition--;
				}
			}else{
				if(randomMovement < 75){
					ypossition++;
				}else{
					ypossition--;
				}
			}
		}
		while(!mapEditor->testBorder(xpossition, ypossition, MOB_WIDTH, MOB_HEIGHT, mobLook)){
			xpossition = tempx;
			ypossition = tempy;
			int randomMovement = rand() %100;
			if(randomMovement < 50){
				if(randomMovement < 25){
					xpossition++;
				}else{
					xpossition--;
				}
			}else{
				if(randomMovement < 75){
					ypossition++;
				}else{
					ypossition--;
				}
			}
		}
	}
	nomovement: mapEditor->drawCharacter(xpossition, ypossition, MOB_WIDTH, MOB_HEIGHT, mobLook);
	if((pow(differencex, 2)+ pow(differencey,2)) < viewDistance){
		detectDamage(mapEditor);
	}
	speedCount++;
}

void Mob::detectDamage(Map*& mapChecker){
	for(int i = xpossition -1; i< xpossition+2;i++){
		char damageIndicator = mapChecker->getBorderCell(i, ypossition);
		if((damageIndicator != '0') && ((speedCount % 6) == 0)){ //we do this to test if he is getting hit and to make sure he doesn't get hit 100 times
			switch(damageIndicator){
			case '6':
				hp -= playerposition->getAttackStrength();
			break;
			case '7':
			break;
			case '8':
			break;
			case '9':
			break;
			}
			break;
		}
	}
}

int Mob::getHealth(){
	return hp;
}

int Mob::getHealthLoot(){
	return healthLoot;
}

int Mob::getDefenceLoot(){
	return defenceLoot;
}

int Mob::getAttackLoot(){
	return attackLoot;
}
int Mob::getHealthAddLoot(){
	return healthAddLoot;
}
Mob::~Mob() {
}

