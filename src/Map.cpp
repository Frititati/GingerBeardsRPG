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

const int rows = 20, columns= 61;

char mapInChar [rows][columns];

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
	//cout << mapInChar[4][2] <<endl;
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
void Map::mapViewPoint(int y, int x, char* strInChar){
	int yincrease = 15, xincrease = 30;		// x is rows
	mapInCharFunc();						// z is columns

	signed int charAt = 0;
//	signed int i = (y - yincrease);
//	signed int iblock = (yincrease*2) + y;
//	if(iblock < 30){
//
//	}
//	signed int iiblock = (xincrease*2) + x;
//	char empty = ' ';
//	while(i < iblock){
//		signed int ii = (x - xincrease);
//		while(ii < iiblock){
//			if(i < 0 || ii < 0 ){
//				strInChar[charAt] = '-';
//			}else if(empty == mapInChar[i][ii] ){
//				strInChar[charAt] = '-';
//			}else {
//				strInChar[charAt] = mapInChar[i][ii];
//			}
//			charAt++;
//			ii++;
//		}
//		strInChar[charAt] = '\n';
//		charAt++;
//		i++;
//	}


	for(int i = (y-yincrease); i<((yincrease*2) + y); i++){
		for(int ii = (x - xincrease); ii<((xincrease*2) + x); ii++){
			if(i < 0 || ii < 0){
				strInChar[charAt] = '-';
			}else{
				strInChar[charAt] = mapInChar[i][ii];
			}
			charAt++;
		}
		strInChar[charAt] = '\n';
		charAt++;
	}
}
