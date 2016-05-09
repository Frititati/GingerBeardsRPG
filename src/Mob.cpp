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

char mobLook [3];

void Mob::mobMovement(Map*& mapEditor, Player*& xyPlayer){
	int tempx = xpossition;
	int tempy = ypossition;
	mobLook[0] = 'G';
	mobLook[1] = 'O';
	mobLook[2] = 'B';
	int playerx;
	int playery;
	xyPlayer->playerPossition(&playerx, &playery);
	int differencex = abs(xpossition - playerx);
	int differencey = abs(ypossition - playery);
	if(differencex < 3 && differencey < 2){
		cout << "Touch" <<endl;
	}
	if((speedCount % speed) == 0){
		if((pow(differencex, 2)+ pow(differencey,2)) < viewDistance){
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
		while(!mapEditor->testBorder(xpossition, ypossition, 3)){
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
	mapEditor->drawCharacter(xpossition, ypossition,mobLook);
	speedCount++;
	oldx = tempx;
	oldy= tempy;
}

bool Mob::testTouch(int x, int y){


	return false;
}
