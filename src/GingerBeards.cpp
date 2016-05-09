#include "gingerbeards.h"
#include "map.h"
#include "player.h"
#include "mob.h"
#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;

const char g_szClassName[] = "myWindowClass";
HWND area;
Map* mapConstructor = new Map();
GingerBeards* tempgingerbeards = new GingerBeards();
Player* firstPlayer = new Player();
Mob* oneMob = new Mob();
char textToBePrinted[10000]; //4*xincrease*yincrease
//int xpossitionnow;
//int ypossitionnow;

	Map*& refMap = mapConstructor;
	HWND& refArea = area;
    switch(msg){
    	case WM_CREATE:
    		area = CreateWindow("static", "broken",
    			WS_VISIBLE| WS_CHILD ,
    			0 , 0 , 300 , 320,
    			hwnd, (HMENU) 1, NULL, NULL
			);
    	break;
    	case WM_KEYDOWN:
    		mapConstructor->refreshEditLayer();	//this is run everytime we call the a key
    		if(wParam == VK_LEFT){
    			oneMob->mobMovement(refMap, firstPlayer);
    			firstPlayer->playerMovement(1, refMap, refArea);
    		}
    		if(wParam == VK_RIGHT){
    			oneMob->mobMovement(refMap, firstPlayer);
    			firstPlayer->playerMovement(2, refMap, refArea);
    		}
    		if(wParam == VK_UP){
    			oneMob->mobMovement(refMap, firstPlayer);
    			firstPlayer->playerMovement(3, refMap, refArea);
			}
			if(wParam == VK_DOWN){
    			oneMob->mobMovement(refMap, firstPlayer);
				firstPlayer->playerMovement(4, refMap, refArea);
			}
			if(wParam == VK_F1){
				oneMob->mobMovement(refMap, firstPlayer);
				firstPlayer->playerMovement(5, refMap, refArea);
			}
		break;


}


	int xpossitionnow = 3;
	int ypossitionnow = 3;
	tempgingerbeards->mapFirstRefresh(xpossitionnow, ypossitionnow);


    ShowWindow(window, nCmdShow);
    UpdateWindow(window);

    while(GetMessage(&Msg, NULL, 0, 0) > 0){
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

	mapConstructor->mapInstantiation();
	mapConstructor->borderInstantion();
	SetWindowText(area, TEXT(textToBePrinted));
}
//void GingerBeards::playerMovement(int keypressed){
//	playerLook[0] = '(';
//	playerLook[1] = '"';
//	playerLook[2] = '-';
//	playerLook[3] = '"';
//	playerLook[4] = ')';
//	int tempx = xpossitionnow;
//	int tempy = ypossitionnow;
//	switch(keypressed){
//	case 1:
//		xpossitionnow--;
//	break;
//	case 2:
//		xpossitionnow++;
//	break;
//	case 3:
//		ypossitionnow--;
//	break;
//	case 4:
//		ypossitionnow++;
//	break;
//	}
//	if(mapConstructor->testBorder(xpossitionnow, ypossitionnow)){
//		mapConstructor->refreshEditLayer();
//		mapConstructor->drawCharacter(xpossitionnow, ypossitionnow,playerLook);
//		mapConstructor->drawCharacter(x2possition, ypossitionnow, playerLook);
//		mapConstructor->mapViewPoint(xpossitionnow,ypossitionnow,textToBePrinted);
//		SetWindowText(area, TEXT(textToBePrinted));
//	}else{
//		xpossitionnow = tempx;
//		ypossitionnow = tempy;
//	}
//}
