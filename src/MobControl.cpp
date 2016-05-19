/*
 * MobControl.cpp
 *
 *  Created on: 19 May 2016
 *      Author: Filippo M Cardano
 */

#include "MobControl.h"
#include "mob.h"
#include <iostream>
using namespace std;

Mob mobArray [5];


MobControl::MobControl(){
	mobArray[0].creatingMob(20, 30);
	mobArray[1].creatingMob(20,40);
	mobArrayLenth = 5;
}

void MobControl::completeAI(Map*& mapEditor, Player*& xyPlayer){
	moveMobs(mapEditor, xyPlayer);
}

void MobControl::moveMobs(Map* mapEditor, Player* xyPlayer){
	for(int i = 0 ; i < mobArrayLenth; i++){
		mobArray[i].mobMovement(mapEditor, xyPlayer);
	}
	checkHealth();
}

void MobControl::checkHealth(){
	int tempMobArrayLength = mobArrayLenth;
	for(int i = 0 ; i < tempMobArrayLength; i++){
		if(mobArray[i].getHealth() < 1){
			mobArrayLenth--;
			int tempcounter = 0;
			for(int j = 0; j < mobArrayLenth; j++){
				if(j != i){
					mobArray[tempcounter] = mobArray[j];
					tempcounter++;
				}
			}
		}
	}
}
MobControl::~MobControl() {
	// TODO Auto-generated destructor stub
}

