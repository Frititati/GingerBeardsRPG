/*
 * GingerBeards.h
 *
 *  Created on: 3 May 2016
 *      Author: Filippo M Cardano
 */

#ifndef GINGERBEARDS_H_
#define GINGERBEARDS_H_

#include <windows.h>
#include "Map.h"

const int STR_IN_CHAR_LENGTH = (VIEWPORT_WIDTH + 1) * VIEWPORT_HEIGHT;
const int FONT_SIZE = 12;
// no rending and collision
const char EMPTY = -1;
// not rendered but collision is still checked.
const char INVISIBLE = -2;
const int GAME_DELAY_MS = 32; //don't change

class GingerBeards{
public:
	void mapFirstRefresh();
	void checkForMenuInput();
	void checkForGameInput();
	void draw(HWND);
	long computeFontHeight();
	void peekMessage();
	void gameLoop();
	void menuLoop();
	void setupGame();
	bool saveGame();
	bool loadGame();
	void intro();
};





#endif /* GINGERBEARDS_H_ */
