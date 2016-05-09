#include "map.h"
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

const int rows = 40, columns= 60;

char mapInChar [rows][columns];
char mapInCharEditable [rows][columns];
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
void Map::mapInstantiation(){
	mapInCharFunc();
	std::copy(&mapInChar[0][0], &mapInChar[0][0]+rows*columns,&mapInCharEditable[0][0]);
}
void Map::mapViewPoint(int x, int y, char* strInChar){
	int yincrease = 20, xincrease = 40;		// x is rows, y is columns

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
				strInChar[charAt] = mapInCharEditable[yi][xi];
			}
//			if(yi == y && xi == (x+1)){
//				strInChar[charAt - 4] = '(';
//				strInChar[charAt - 3] = '‘';
//				strInChar[charAt - 2] = '-';
//				strInChar[charAt - 1] = '‘';
//				strInChar[charAt] = ')';
//			}
			charAt++;
			xi++;
		}
		strInChar[charAt] = '\n';
		charAt++;
		yi++;
	}
}
void Map::borderInstantion(){
	borderInCharFunc();
}
bool Map::testBorder(int x, int y, int size){
	int sizeHelper = (size/2);
	for(int i = (x - sizeHelper); i <= (x+sizeHelper); i++){
		if(borderInChar[y][i] == '1'){
			return false;
		}
	}
	return true;
}
void Map::refreshEditLayer(){
	std::copy(&mapInChar[0][0], &mapInChar[0][0]+rows*columns,&mapInCharEditable[0][0]);
}
void Map::drawCharacter(int x, int y, char* drawPoints){
	signed int lenght = strlen(drawPoints);
	if(lenght == 5){
		mapInCharEditable[y][x - 2] = drawPoints[0];
		mapInCharEditable[y ][x- 1] = drawPoints[1];
		mapInCharEditable[y][x] = drawPoints[2];
		mapInCharEditable[y ][x+ 1] = drawPoints[3];
		mapInCharEditable[y][x + 2] = drawPoints[4];
	}
	if(lenght == 3){
		mapInCharEditable[y ][x- 1] = drawPoints[0];
		mapInCharEditable[y][x] = drawPoints[1];
		mapInCharEditable[y ][x+ 1] = drawPoints[2];
	}
	if(lenght == 1){
			mapInCharEditable[y][x] = drawPoints[0];
	}
}

