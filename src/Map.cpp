/*
 * Map.cpp
 *
 *  Created on: 20 Apr 2016
 *      Author: Filippo M Cardano
 */
#include "map.h"
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

const int rows = 20, columns= 60;

char mapInChar [rows][columns];
char borderInChar [rows][columns];

void Map::mapInCharFunc(){
	string line;
	ifstream myfile ("bordercontrol.txt");
	if (myfile.is_open()){
		int a = 0;
		while(getline(myfile,line)){
			for(unsigned int i = 0; i < line.length(); i++){
				mapInChar[a][i] = line.at(i);
			}
			a++;
		}
		myfile.close();
	} else{
		cout << "Unable to open file" << endl;
	}
}
void Map::borderInCharFunc(){
	string line;
	ifstream myfile ("control.txt");
	if (myfile.is_open()){
		int a = 0;
		while(getline(myfile,line)){
			for(unsigned int i = 0; i < line.length(); i++){
				borderInChar[a][i] = line.at(i);
			}
			a++;
		}
		myfile.close();
	} else{
		cout << "Unable to open file" << endl;
	}
}
void Map::getVarOfMap(char* strInChar){
	mapInCharFunc();
	int chatAt = 0;
	for(int i = 0; i<rows; i++){
		for(int ii = 0; ii<columns; ii++){
			strInChar[chatAt] = mapInChar[i][ii];
			chatAt++;
		}
		strInChar[chatAt] = '\n';
		chatAt++;
	}
}
void Map::mapViewPoint(int x, int y, char* strInChar){
	int yincrease = 20, xincrease = 40;		// x is rows, y is columns
	mapInCharFunc();

	signed int charAt = 0;
	signed int yi = (y - yincrease);
	signed int yblock = yincrease + y;
	signed int xblock = xincrease + x;
	while(yi < yblock){
		signed int xi = (x - xincrease);
		while(xi < xblock){
			if(yi < 0 || xi < 0 || yi >= rows || xi >= columns){
				strInChar[charAt] = '-';
			} else {
				strInChar[charAt] = mapInChar[yi][xi];
			}
			if(yi == y && xi == (x+1)){
				strInChar[charAt - 2] = '¶';
				strInChar[charAt - 1] = '¶';
				strInChar[charAt] = '¶';
			}
			charAt++;
			xi++;
		}
		strInChar[charAt] = '\n';
		charAt++;
		yi++;
	}
//	for(int i = (y-yincrease); i<((yincrease*2) + y); i++){
//		for(int ii = (x - xincrease); ii<((xincrease*2) + x); ii++){
//			if(i < 0 || ii < 0){
//				strInChar[charAt] = '-';
//			}else{
//				strInChar[charAt] = mapInChar[i][ii];
//			}
//			charAt++;
//		}
//		strInChar[charAt] = '\n';
//		charAt++;
//	}
}
bool Map::testBorder(int x, int y){
	borderInCharFunc();
	if(borderInChar[y][x] == '1'){
		return false;
	}else{
		return true;
	}
}

