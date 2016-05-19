#include "map.h"
#include "GingerBeards.h"
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

char mapInChar[MAP_ROWS][MAP_COLUMNS];
char mapInCharEditable[VIEWPORT_HEIGHT][VIEWPORT_WIDTH];
char borderInChar[MAP_ROWS][MAP_COLUMNS];
char borderInCharRestore[MAP_ROWS][MAP_COLUMNS];

int viewportX, viewportY;

void Map::mapInCharFunc() {
	string line;
	ifstream myfile("map2.txt");
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
	ifstream myfile("collisionmap2.txt");
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
			if (absoluteY < 0 || absoluteX < 0 || absoluteY >= MAP_ROWS
					|| absoluteX >= MAP_COLUMNS) {
				mapInCharEditable[yi][xi] = '-';
			} else {
				mapInCharEditable[yi][xi] = mapInChar[absoluteY][absoluteX];
			}
		}
	}
//	for (int i = 0; i < MAP_ROWS; i++){
//		for(int j =0; j < MAP_COLUMNS; j++){
//		}
//	}
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
	std::copy(&borderInChar[0][0], &borderInChar[0][0]+MAP_ROWS*MAP_COLUMNS,&borderInCharRestore[0][0]);
}

bool Map::testBorder(int x, int y, int width, int height, char** look) {
	int widthHelper = width / 2, heightHelper = height / 2;
	for (int i = y - heightHelper, li = 0; i <= y + heightHelper; i++, li++) {
		for (int j = x - widthHelper, lj = 0; j <= x + widthHelper; j++, lj++) {
			if (look[li][lj] != EMPTY && borderInChar[i][j] == '1') {
				return false;
			}
		}
	}
	return true;
}

void Map::refreshEditLayer() {
	std::copy(&mapInChar[0][0], &mapInChar[0][0] + MAP_ROWS * MAP_COLUMNS,
			&mapInCharEditable[0][0]);
}

void Map::drawCharacter(int x, int y, int drawWidth, int drawHeight,
		char** drawPoints) {
	// coordinates relative to the viewport
	int viewportRelativeX = x - viewportX;
	int viewportRelativeY = y - viewportY;
	int leftmostChar = viewportRelativeX - drawWidth / 2;
	int topmostChar = viewportRelativeY - drawHeight / 2;
	int bottommostChar;
	if (topmostChar >= 0) {
		for (int i = 0; topmostChar + i < VIEWPORT_HEIGHT && i < drawHeight;
				i++) {
			drawCharacterXAxis(leftmostChar, topmostChar + i, drawWidth, i,
					drawPoints);
		}
	} else if ((bottommostChar = viewportRelativeY + drawHeight / 2)
			< VIEWPORT_HEIGHT) {
		for (int i = 0; bottommostChar - i >= 0 && i < drawHeight; i++) {
			drawCharacterXAxis(leftmostChar, bottommostChar - i, drawWidth,
					drawHeight - i - 1, drawPoints);
		}
	} else {
		cout << "The character is longer than the viewport!" << endl;
	}
}
void Map::drawChar(int x, int y, char draw) {
	// coordinates relative to the viewport
	int viewportRelativeX = x - viewportX;
	int viewportRelativeY = y - viewportY;
	mapInCharEditable[viewportRelativeY][viewportRelativeX] = draw;
}

void Map::drawCharacterXAxis(int leftmostChar, int y, int drawWidth, int i, char** drawPoints) {
	int rightmostChar;
	if (leftmostChar >= 0) {
		for (int j = 0; leftmostChar + j < VIEWPORT_WIDTH && j < drawWidth;
				j++) {
			char charToBeDrawn = drawPoints[i][j];
			if (charToBeDrawn != EMPTY) {
				mapInCharEditable[y][leftmostChar + j] = charToBeDrawn;
			}
		}
	} else if ((rightmostChar = leftmostChar + drawWidth - 1)
			< VIEWPORT_WIDTH) {
		for (int j = 0; rightmostChar - j >= 0 && j < drawWidth; j++) {
			char charToBeDrawn = drawPoints[i][drawWidth - j - 1];
			if (charToBeDrawn != EMPTY) {
				mapInCharEditable[y][rightmostChar - j] = charToBeDrawn;
			}
		}
	} else {
		cout << "The character is wider than the viewport!" << endl;
	}
}

void Map::restoreBorder(){
	std::copy(&borderInCharRestore[0][0], &borderInCharRestore[0][0]+MAP_ROWS*MAP_COLUMNS,&borderInChar[0][0]);
}

void Map::editBorder(int x, int y, char charEdited){
	if(borderInChar[y][x] != '1'){
		borderInChar[y][x] = charEdited;
	}
}
char Map::getBorderCell(int x, int y){
	return borderInChar[y][x];
}



//void Map::getBorders(char** getBorders){
//	for(int i=0; i < MAP_ROWS; i++){
//		for(int j=0; j< MAP_COLUMNS; j++){
//			getBorders[i][j] = borderInChar[i][j];
//		}
//	}
//}


