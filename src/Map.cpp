#include "map.h"
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

char mapInChar[ROWS][COLUMNS];
char mapInCharEditable[VIEWPORT_HEIGHT][VIEWPORT_WIDTH];
char borderInChar[ROWS][COLUMNS];

int viewportX, viewportY;

void Map::mapInCharFunc() {
	string line;
	ifstream myfile("bordercontrol.txt");
	if (myfile.is_open()) {
		int a = 0;
		while (getline(myfile, line)) {
			for (unsigned int i = 0; i < line.length(); i++) {
				mapInChar[a][i] = line.at(i);
			}
			a++;
		}
		myfile.close();
	} else {
		cout << "Unable to open file" << endl;
	}
}
void Map::borderInCharFunc() {
	string line;
	ifstream myfile("control.txt");
	if (myfile.is_open()) {
		int a = 0;
		while (getline(myfile, line)) {
			for (unsigned int i = 0; i < line.length(); i++) {
				borderInChar[a][i] = line.at(i);
			}
			a++;
		}
		myfile.close();
	} else {
		cout << "Unable to open file" << endl;
	}
}
//void Map::getVarOfMap(char* strInChar){
//	mapInCharFunc();
//	int chatAt = 0;
//	for(int i = 0; i<rows; i++){
//		for(int ii = 0; ii<columns; ii++){
//			strInChar[chatAt] = mapInChar[i][ii];
//			chatAt++;
//		}
//		strInChar[chatAt] = '\n';
//		chatAt++;
//	}
//}
void Map::mapInstantiation() {
	mapInCharFunc();
//	std::copy(&mapInChar[0][0], &mapInChar[0][0]+ROWS*COLUMNS,&mapInCharEditable[0][0]);
}
void Map::mapViewPort(int x, int y) {
	viewportX = x - XINCREASE;
	viewportY = y - YINCREASE;
	for (int yi = 0; yi < VIEWPORT_HEIGHT; yi++) {
		int absoluteY = viewportY + yi;
		for (int xi = 0; xi < VIEWPORT_WIDTH; xi++) {
			int absoluteX = viewportX + xi;
			if (absoluteY < 0 || absoluteX < 0 || absoluteY >= ROWS || absoluteX >= COLUMNS) {
				mapInCharEditable[yi][xi] = '-';
			} else {
				mapInCharEditable[yi][xi] = mapInChar[absoluteY][absoluteX];
			}
		}
	}
}

void Map::getStrInChar(char* strInChar) {
	for (int i = 0, charAt = 0; i < VIEWPORT_HEIGHT; i++, charAt++) {
		for (int j = 0; j < VIEWPORT_WIDTH; j++, charAt++) {
			strInChar[charAt] = mapInCharEditable[i][j];
		}
		strInChar[charAt] = '\n';
	}
}

void Map::borderInstantion() {
	borderInCharFunc();
}

bool Map::testBorder(int x, int y, int size) {
	int sizeHelper = (size / 2);
	for (int i = (x - sizeHelper); i <= (x + sizeHelper); i++) {
		if (borderInChar[y][i] == '1') {
			return false;
		}
	}
	return true;
}
void Map::refreshEditLayer() {
	std::copy(&mapInChar[0][0], &mapInChar[0][0] + ROWS * COLUMNS,
			&mapInCharEditable[0][0]);
}
void Map::drawCharacter(int x, int y, char* drawPoints) {
	signed int length = strlen(drawPoints);
	int relativeX = x - viewportX;
	int relativeY = y - viewportY;
	int sizeHelper = length / 2;
	// maybe expand to a for in the future, so that it is possible to have two-dimensional characters
	if (relativeY < 0)
		return;
	for (int i = relativeX + sizeHelper, j = length - 1; i >= 0 && j >= 0;
			i--, j--) {
		mapInCharEditable[relativeY][i] = drawPoints[j];
	}
}

