/*
 * Player.cpp
 *
 *  Created on: 25.04.2016
 *      Author: Michele
 */

#include "Player.h"
#include "GingerBeards.h"
#include <windows.h>

char playerLook [5];
int xpossitionnow = 3;
int ypossitionnow = 3;
char toBePrinted[1000];

int Player::playerMovement(int keypressed, Map mapEditor, HWND areaEdit ){
	int tempx = xpossitionnow;
	int tempy = ypossitionnow;
	switch(keypressed){
	case 1:
		xpossitionnow--;
	break;
	case 2:
		xpossitionnow++;
	break;
	case 3:
		ypossitionnow--;
	break;
	case 4:
		ypossitionnow++;
	break;
	}
	if(mapEditor.testBorder(xpossitionnow, ypossitionnow)){
		mapEditor.refreshEditLayer();
		mapEditor.drawCharacter(xpossitionnow, ypossitionnow,playerLook);
		//mapEditor->drawCharacter(x2possition, ypossitionnow, playerLook);
		mapEditor.mapViewPoint(xpossitionnow,ypossitionnow,toBePrinted);
		SetWindowText(areaEdit, TEXT(toBePrinted));
	}else{
		xpossitionnow = tempx;
		ypossitionnow = tempy;
	}
	return 1;
}

