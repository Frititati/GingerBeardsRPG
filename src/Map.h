/*
 * Map
 *
 *  Created on: 25 Apr 2016
 *      Author: Filippo M Cardano
 */

#ifndef MAP_H_
#define MAP_H_
#include <string.h>

const int XINCREASE = 45, YINCREASE = 15;
const int VIEWPORT_WIDTH = 2 * XINCREASE + 1;
const int VIEWPORT_HEIGHT = 2 * YINCREASE + 1;
const int MAP_ROWS = 181, MAP_COLUMNS= 400;

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
	void refreshEditLayer();
	void getStrInChar(char*);
private:
	void drawCharacterXAxis(int, int, int, int, char**);
};



#endif /* MAP_H_ */
