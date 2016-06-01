/*
 * MobControl.cpp
 *
 *  Created on: 19 May 2016
 *      Author: Filippo M Cardano
 */

#include "MobControl.h"
#include "mob.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Mob mobArray [30];


MobControl::MobControl(){
	mobArrayLenth = 0;
	counter=0;
}

void MobControl::completeAI(Map*& mapEditor, Player*& xyPlayer){
	moveMobs(mapEditor, xyPlayer);
	if(checkHealth(xyPlayer)){
		int x =0;
		int y = 0;
		xyPlayer->playerPosition(&x, &y);
		mapEditor->drawChar(x, y - 2, '*');
		mapEditor->drawChar(x-1, y - 2, '*');
		mapEditor->drawChar(x+1, y - 2, '*');
	}
	if((counter % 30) == 0){
		smartSpawn(xyPlayer, mapEditor);
		counter = 0;
	}
	smartDespawn();
	counter++;
}

void MobControl::moveMobs(Map* mapEditor, Player* xyPlayer){
	for(int i = 0 ; i < mobArrayLenth; i++){
		mobArray[i].mobMovement(mapEditor, xyPlayer);
	}
}

void MobControl::smartDespawn(){
	int tempMobArrayLength = mobArrayLenth;
	for(int i = 0 ; i < tempMobArrayLength; i++){
		if(mobArray[i].despawnCheck()){
			mobArrayLenth--;
			int tempcounter = 0;
			for(int j = 0; j < tempMobArrayLength; j++){
				if(j != i){
					mobArray[tempcounter] = mobArray[j];
					tempcounter++;
				}
			}
		}
	}
}

bool MobControl::checkHealth(Player*& addStats){
	int tempMobArrayLength = mobArrayLenth;
	bool what = false;
	for(int i = 0 ; i < tempMobArrayLength; i++){
		if(mobArray[i].getHealth() < 1){
			mobArrayLenth--;
			addStats->setMaxHP(mobArray[i].getHealthAddLoot()+ addStats->getMaxHP());
			addStats->addHP(mobArray[i].getHealthLoot());//add gets
			addStats->addDef(mobArray[i].getDefenceLoot());
			addStats->addAtk(mobArray[i].getAttackLoot());
			int tempcounter = 0;
			for(int j = 0; j < tempMobArrayLength; j++){
				if(j != i){
					mobArray[tempcounter] = mobArray[j];
					tempcounter++;
				}
			}
			what = true;
		}
	}
	return what;
}
void MobControl::smartSpawn(Player*& playerinfo, Map*& mapChecker){
	int x;
	int y;
	playerinfo->playerPosition(&x,&y);
	int idealx = rand() % 40 + (x - 20);
	int idealy = rand() % 30 + (y - 15);
	char** mobLook = new char *[MOB_HEIGHT];
	mobLook[0] = new char[MOB_WIDTH];
	mobLook[0][0] = 'M';
	mobLook[0][1] = 'M';
	mobLook[0][2] = 'M';
	if(mobArrayLenth < 28 && mapChecker->testBorder(idealx, idealy, 3, 1, mobLook)){
		mobArray[mobArrayLenth].creatingMob(idealx, idealy, playerinfo);
		mobArrayLenth++;
	}
}
MobControl::~MobControl() {
	// TODO Auto-generated destructor stub
}

