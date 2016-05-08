/*
 * Map
 *
 *  Created on: 25 Apr 2016
 *      Author: Filippo M Cardano
 */

#ifndef MAP_H_
#define MAP_H_
#include <string.h>

class Map{
public:
	void mapInCharFunc();
	void borderInCharFunc();
	//void getVarOfMap(char* stringMap);
	void mapViewPoint(int x, int y, char* strInChar);
	bool testBorder(int x, int y);
	void mapInstantiation();
	void borderInstantion();
	void drawCharacter(int, int, char*);
	void refreshEditLayer();
};



#endif /* MAP_H_ */
