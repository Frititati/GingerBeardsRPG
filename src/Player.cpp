#include "Player.h"
#include "GingerBeards.h"
#include <windows.h>
#include <iostream>
using namespace std;

char playerLook[] = {'(', '"', '-', '"', ')'};
char toBePrinted[500000];


void Player::playerMovement(int keypressed, Map*& mapEditor){
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
	if(!mapEditor->testBorder(xpossition, ypossition, 5)){
		xpossition = tempx;
		ypossition = tempy;
	}
	mapEditor->drawCharacter(xpossition, ypossition,playerLook);
}
void Player::playerPossition(int* x, int* y){
	*x = xpossition;
	*y = ypossition;
}

