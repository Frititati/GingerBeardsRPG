/*
 * GingerBeards.h
 *
 *  Created on: 3 May 2016
 *      Author: Filippo M Cardano
 */

#ifndef GINGERBEARDS_H_
#define GINGERBEARDS_H_

#include "Map.h"

const int STR_IN_CHAR_LENGTH = (VIEWPORT_WIDTH + 1) * VIEWPORT_HEIGHT;
const int FONT_SIZE = 12;
const char EMPTY = ' ';

class GingerBeards{
public:
	void mapFirstRefresh();
	bool checkForInput();
	void draw();
	long computeFontHeight();
	int test;

};





#endif /* GINGERBEARDS_H_ */
