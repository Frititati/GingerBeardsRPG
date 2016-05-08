#include "gingerbeards.h"
#include "map.h"
#include "player.h"
#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;

const char g_szClassName[] = "myWindowClass";
HWND area;
Map* mapConstructor = new Map();
GingerBeards* tempgingerbeards = new GingerBeards();
Player* firstPlayer = new Player();
char textToBePrinted[1000];
int xpossitionnow;
int ypossitionnow;
int x2possition = 5;
char playerLook2 [5];

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
    	case WM_CREATE:
    		area = CreateWindow("static", "broken",
    			WS_VISIBLE| WS_CHILD ,
    			0 , 0 , 300 , 320,
    			hwnd, (HMENU) 1, NULL, NULL
			);
    	break;
    	case WM_KEYDOWN:
    		HWND& testarea = area;
    		Map* fuckthisshit = mapConstructor;
    		if(wParam == VK_LEFT){
    			firstPlayer->playerMovement(1, fuckthisshit, testarea);
    		}
    		if(wParam == VK_RIGHT){
    			firstPlayer->playerMovement(2, mapConstructor, area);
    		}
    		if(wParam == VK_UP){
    			firstPlayer->playerMovement(3, mapConstructor, area);
			}
			if(wParam == VK_DOWN){
				firstPlayer->playerMovement(4, mapConstructor, area);
			}
		break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    WNDCLASSEX wc;
    HWND window;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)){
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    window = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "ASCII RPG",
        WS_OVERLAPPEDWINDOW,
        50, 100, 350, 370,
        NULL, NULL, hInstance, NULL);

	HFONT hfReg = CreateFont(15, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, TEXT("CONSOLAS"));
	SendMessage(area,WM_SETFONT,(WPARAM)hfReg,MAKELPARAM(FALSE,0));


	xpossitionnow = 3;
	ypossitionnow = 3;
	tempgingerbeards->mapFirstRefresh(xpossitionnow, ypossitionnow);

    if(window == NULL){
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(window, nCmdShow);
    UpdateWindow(window);

    while(GetMessage(&Msg, NULL, 0, 0) > 0){
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

void GingerBeards::mapFirstRefresh(int x, int y){
	mapConstructor->mapInstantiation();
	mapConstructor->borderInstantion();
	mapConstructor->drawCharacter(x,y,playerLook2);
	mapConstructor->mapViewPoint(x,y,textToBePrinted);
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
