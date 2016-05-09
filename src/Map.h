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
const int ROWS = 40, COLUMNS= 60;

class Map{
public:
	void mapInCharFunc();
	void borderInCharFunc();
	//void getVarOfMap(char* stringMap);
	void mapViewPoint(int x, int y, char* strInChar);
	bool testBorder(int x, int y, int size);
	void mapInstantiation();
	void borderInstantion();
	void drawCharacter(int, int, char*);
	void refreshEditLayer();
};



#endif /* MAP_H_ */
