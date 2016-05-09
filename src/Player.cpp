#include "Player.h"
#include "GingerBeards.h"
#include <windows.h>
#include <iostream>
using namespace std;

char playerLook [5];
char toBePrinted[500000];

void Player::playerMovement(int keypressed, Map*& mapEditor){
	playerLook[0] = '(';
	playerLook[1] = '"';
	playerLook[2] = '-';
	playerLook[3] = '"';
	playerLook[4] = ')';
	int tempx = xpossition;
	int tempy = ypossition;
	switch(keypressed){
	case 1:
		xpossition--;
	break;
	case 2:
		xpossition++;
	break;
	case 3:
		ypossition--;
	break;
	case 4:
		ypossition++;
	break;
	case 5:
	break;
	}
	if(mapEditor->testBorder(xpossition, ypossition, 5)){
		mapEditor->drawCharacter(xpossition, ypossition,playerLook);
		//mapEditor->mapViewPoint(xpossition,ypossition,toBePrinted);
		//SetWindowText(textArea, TEXT(toBePrinted));
	}else{
		xpossition = tempx;
		ypossition = tempy;
	}
}
void Player::playerPossition(int* x, int* y){
	*x = xpossition;
	*y = ypossition;
}

