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
// left is the x coordinate of the top left vertex of the game, top is the y
const int RECT_LEFT = 80;
const int RECT_TOP = 10;

class GingerBeards{
public:
	void mapFirstRefresh(int, int);
	void checkForInput();
	void draw(HWND);
	long computeFontHeight();

};





#endif /* GINGERBEARDS_H_ */
