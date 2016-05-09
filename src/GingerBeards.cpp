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

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE:
		area = CreateWindow("static", "broken",
				WS_VISIBLE| WS_CHILD ,
				0 , 0 , 1000 , 1000,
				hwnd, (HMENU) 1, NULL, NULL
		);
		break;
//    	case WM_KEYDOWN:
//    		mapConstructor->refreshEditLayer();	//this is run everytime we call the a key
//    		if(wParam == VK_LEFT){
//    			oneMob->mobMovement(refMap, firstPlayer);
//    			firstPlayer->playerMovement(1, refMap, refArea);
//    		}
//    		if(wParam == VK_RIGHT){
//    			oneMob->mobMovement(refMap, firstPlayer);
//    			firstPlayer->playerMovement(2, refMap, refArea);
//    		}
//    		if(wParam == VK_UP){
//    			oneMob->mobMovement(refMap, firstPlayer);
//    			firstPlayer->playerMovement(3, refMap, refArea);
//			}
//			if(wParam == VK_DOWN){
//    			oneMob->mobMovement(refMap, firstPlayer);
//				firstPlayer->playerMovement(4, refMap, refArea);
//			}
//			if(wParam == VK_F1){
//				oneMob->mobMovement(refMap, firstPlayer);
//				firstPlayer->playerMovement(5, refMap, refArea);
//			}
//		break;

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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND window;
	MSG Msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!",
		MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	window = CreateWindowEx(
	WS_EX_CLIENTEDGE, g_szClassName, "ASCII RPG",
	WS_OVERLAPPEDWINDOW, 50, 100, 350, 370,
	NULL, NULL, hInstance, NULL);

	HFONT hfReg = CreateFont(15, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0,
			TEXT("CONSOLAS"));
	SendMessage(area, WM_SETFONT, (WPARAM) hfReg, MAKELPARAM(FALSE, 0));

	int xpossitionnow = 3;
	int ypossitionnow = 3;
	tempgingerbeards->mapFirstRefresh(xpossitionnow, ypossitionnow);

	if (window == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!",
		MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(window, nCmdShow);
	UpdateWindow(window);

	// this approach is really slow.
//    while(GetMessage(&Msg, NULL, 0, 0) > 0){
//        TranslateMessage(&Msg);
//        DispatchMessage(&Msg);
//    }
	Map*& refMap = mapConstructor;
	while (1)  // LOOP FOREVER
	{
		// 1.  PROCESS MESSAGES FROM WINDOWS
		if ( PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
			// Now, this is DIFFERENT than GetMessage()!
			// PeekMessage is NOT a BLOCKING FUNCTION.
			// That is, PeekMessage() returns immediately
			// with either a TRUE (there was a message
			// for our window)
			// or a FALSE (there was no message for our window).

			// If there was a message for our window, then
			// we want to translate and dispatch that message.

			// otherwise, we want to be free to run
			// the next frame of our program.
			if (Msg.message == WM_QUIT) {
				break;  // BREAK OUT OF INFINITE LOOP
						// if user is trying to quit!
			} else {
				TranslateMessage(&Msg);   // translates
				DispatchMessage(&Msg);    // this line RESULTS IN
				// a call to WndProc(), passing the message and
				// the HWND.

				// Note that in this program, all we're really using
				// the messaging system for is for
				// processing the QUIT message that occurs
				// when the user clicks the X on the window
				// to close it.

				// ALL OTHER application processing happens
				// in the 3 lines of code below
				// (the 'check_for_user ... ' stuff)
			}
		} else {
			mapConstructor->refreshEditLayer();
			tempgingerbeards->checkForInput();
		}
		Sleep(16.0);
	}

	return Msg.wParam;
}

void GingerBeards::checkForInput() {
	Map*& refMap = mapConstructor;
	HWND& refArea = area;
	if (GetAsyncKeyState( VK_UP)) {
		oneMob->mobMovement(refMap, firstPlayer);
		firstPlayer->playerMovement(3, refMap, refArea);
	}

	if (GetAsyncKeyState( VK_DOWN)) {
		oneMob->mobMovement(refMap, firstPlayer);
		firstPlayer->playerMovement(4, refMap, refArea);
	}

	if (GetAsyncKeyState( VK_RIGHT)) {
		firstPlayer->playerMovement(2, refMap, refArea);
		oneMob->mobMovement(refMap, firstPlayer);
	}

	if (GetAsyncKeyState( VK_LEFT)) {
		firstPlayer->playerMovement(1, refMap, refArea);
		oneMob->mobMovement(refMap, firstPlayer);
	}
	if (GetAsyncKeyState(VK_F1)) {
		firstPlayer->playerMovement(5, refMap, refArea);
		oneMob->mobMovement(refMap, firstPlayer);
	}
}

void GingerBeards::mapFirstRefresh(int x, int y) {
	mapConstructor->mapInstantiation();
	mapConstructor->borderInstantion();
	mapConstructor->mapViewPoint(x, y, textToBePrinted);
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
