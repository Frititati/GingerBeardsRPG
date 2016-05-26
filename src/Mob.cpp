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
using namespace std;

char** mobLook;
Player* playerposition;

Mob::Mob(){
	mobLook = new char *[MOB_HEIGHT];
	hp = 3;
		speedCount = 0;
		xpossition = 30;
		ypossition = 30;
		speed = 7;
		viewDistance = 400;
}

void Mob::creatingMob(int x, int y) {
	mobLook = new char *[MOB_HEIGHT];
	mobLook[0] = new char[MOB_WIDTH];
	mobLook[0][0] = 'G';
	mobLook[0][1] = 'O';
	mobLook[0][2] = 'B';
//	for(int i = 0; i <10; i++)
//	    array[i] = new int[10];
	hp = 17;
	attackStrength = 15;
	speedCount = 0;
	xpossition = x;
	ypossition = y;
	speed = 5;
	viewDistance = 400; // sqrt(10)
	aggressive = true;
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

Mob::~Mob() {
}
