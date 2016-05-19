/*
 * MobControl.h
 *
 *  Created on: 19 May 2016
 *      Author: Filippo M Cardano
 */

#ifndef SRC_MOBCONTROL_H_
#define SRC_MOBCONTROL_H_
#include "mob.h"

class MobControl {
public:
	MobControl();
	virtual ~MobControl();
	void moveMobs(Map*, Player*);
	void checkHealth();
	void completeAI(Map*&, Player*&);
private:
	int mobArrayLenth;
};

#endif /* SRC_MOBCONTROL_H_ */
