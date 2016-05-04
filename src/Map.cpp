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

const int rows = 20, columns= 131;

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
	int yincrease = 15, xincrease = 30;		// x is rows
	mapInCharFunc();						// z is columns

	signed int charAt = 0;
	signed int i = (y - yincrease);
	signed int iblock = (yincrease*2) + y;
	signed int iiblock = (xincrease*2) + x;
	while(i < iblock){
		signed int ii = (x - xincrease);
		while(ii < iiblock){
			if(i < 0 || ii < 0 ){
				strInChar[charAt] = '-';
			}else {
				strInChar[charAt] = mapInChar[i][ii];
			}
			if(i == y && ii == (x+1)){
				strInChar[charAt - 2] = '¶';
				strInChar[charAt - 1] = '¶';
				strInChar[charAt] = '¶';
			}
			charAt++;
			ii++;
		}
		strInChar[charAt] = '\n';
		charAt++;
		i++;
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

