/*
 * Map
 *
 *  Created on: 25 Apr 2016
 *      Author: Filippo M Cardano
 */

#ifndef MAP_H_
#define MAP_H_
#include <string.h>

const int XINCREASE = 72, YINCREASE = 18;
const int VIEWPORT_WIDTH = 2 * XINCREASE + 1;
const int VIEWPORT_HEIGHT = 2 * YINCREASE + 1;
const int MAP_HEIGHT = 181, MAP_WIDTH= 400;
const int DIGITS = 5;
const int HEALTHBAR_WIDTH = 41;

const char PLAYER_SWING = '6';
const char AOE = '7';

class Map{
public:
	void mapInCharFunc();
	void borderInCharFunc();
	//void getVarOfMap(char* stringMap);
	void mapViewPort(int x, int y);
	bool testBorder(int , int , int, int, char**);
	void mapInstantiation();
	void borderInstantion();
	void drawCharacter(int, int, int, int, char**);
	void drawChar(int, int, char);
	void drawChar(int, int, char, char);
	void drawStatsBar(int, int, int, int);
	void drawMenu();
	void refreshEditLayer();
	void getStrInChar(char*);
//	void getBorders(char**);
	void editBorder(int, int, char);
	void restoreBorder();
	void restoreBorderCell(int x, int y);
	char getBorderCell(int, int);
private:
	char* toChar(int, int*);
	void drawCharacterXAxis(int, int, int, int, char**);
	int drawStat(int j, int stat, char* label, int labelSize);
};



#endif /* MAP_H_ */
