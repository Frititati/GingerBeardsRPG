/*
 * MobControl.h
 *
 *  Created on: 19 May 2016
 *      Author: Filippo M Cardano
 */

#ifndef SRC_MOBCONTROL_H_
#define SRC_MOBCONTROL_H_
#include "Mob.h"

class MobControl {
public:
	MobControl();
	virtual ~MobControl();
	void moveMobs(Map*, Player*);
	bool checkHealth(Player*&);
	void completeAI(Map*&, Player*&);
	void smartSpawn(Player*&, Map*&);
	void smartDespawn();
private:
	int mobArrayLenth;
	unsigned int counter;
};

#endif /* SRC_MOBCONTROL_H_ */
