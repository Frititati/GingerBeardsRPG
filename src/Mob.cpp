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
using namespace std;

char mobLook [3];

void Mob::mobMovement(Map*& mapEditor, Player*& xyPlayer){
	int playerx;
	int playery;
	xyPlayer->playerPossition(&playerx, &playery);
	unsigned int differencex = xpossition - playerx;
	unsigned int differencey = ypossition - playery;
	if(differencex < 11 && differencey < 11){
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
	}

	int tempx = xpossition;
	int tempy = ypossition;
	mobLook[0] = 'G';
	mobLook[1] = 'O';
	mobLook[2] = 'B';
//	int randomMovement = rand() %100;
//	if(randomMovement < 50){
//		if(randomMovement < 25){
//			xpossition++;
//		}else{
//			xpossition--;
//		}
//	}else{
//		if(randomMovement < 75){
//			ypossition++;
//		}else{
//			ypossition--;
//		}
//	}

	while(!mapEditor->testBorder(xpossition, ypossition)){
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
	mapEditor->drawCharacter(xpossition, ypossition,mobLook);
	oldx = tempx;
	oldy= tempy;
}
