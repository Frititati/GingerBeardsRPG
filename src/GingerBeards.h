/*
 * GingerBeards.h
 *
 *  Created on: 3 May 2016
 *      Author: Filippo M Cardano
 */

#ifndef GINGERBEARDS_H_
#define GINGERBEARDS_H_

#include <windows.h>
#include "map.h"

const int LENGTH = 4 * XINCREASE * YINCREASE + ROWS;
const int FONT_SIZE = 12;

class GingerBeards{
public:
	void mapFirstRefresh(int, int);
	void checkForInput();
	void draw(HWND);
	long computeFontHeight();

};





#endif /* GINGERBEARDS_H_ */
