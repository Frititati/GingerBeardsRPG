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

const int rows = 254, columns= 400;

char mapInChar [rows][columns];

void Map::mapInCharFunc(){
	string line;
	ifstream myfile ("trialmap.txt");
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
//	string tmp = "cat";
//	strncpy(strInChar, tmp.c_str(), sizeof(strInChar));
//	strInChar[sizeof(strInChar) - 1] = 0;
}
void Map::mapViewPoint(int x, int z, char* strInChar){
	int xincrease = 15, zincrease = 30;
	mapInCharFunc();
	int charAt = 0;
	for(int i = (x-xincrease); i<((xincrease*2) + x); i++){
		for(int ii = (z - zincrease); ii<((zincrease*2)+z); ii++){
			strInChar[charAt] = mapInChar[i][ii];
			charAt++;
		}
		strInChar[charAt] = '\n';
		charAt++;
	}
}
