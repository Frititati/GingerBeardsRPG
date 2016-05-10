#include "gingerbeards.h"
#include "player.h"
#include "mob.h"
#include <iostream>
#include <fstream>
using namespace std;

const char g_szClassName[] = "myWindowClass";
//HWND area;
Map* mapConstructor = new Map();
GingerBeards* tempgingerbeards = new GingerBeards();
Player* firstPlayer = new Player();
Mob* oneMob = new Mob();

char textToBePrinted[STR_IN_CHAR_LENGTH];

long lfHeight = tempgingerbeards->computeFontHeight();

// get the height of the font based on device units
long GingerBeards::computeFontHeight() {
	HDC hdc = GetDC(NULL);
	long result = -MulDiv(FONT_SIZE, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	ReleaseDC(NULL, hdc);
	return result;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
//	case WM_CREATE:
//		area = CreateWindow("static", NULL,
//				WS_VISIBLE| WS_CHILD,
//				0 , 0 , 700 , 700,
//				hwnd, (HMENU) 1, NULL, NULL
//		);
//		break;
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
	WS_OVERLAPPEDWINDOW, 50, 100, 1000, 1000,
	NULL, NULL, hInstance, NULL);

	if (window == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!",
		MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	tempgingerbeards->mapFirstRefresh();

	ShowWindow(window, nCmdShow);
	UpdateWindow(window);

	Map*& refMap = mapConstructor;
	while (1) {  // LOOP FOREVER
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
			if (Msg.message == WM_QUIT) {
				break;  // BREAK OUT OF INFINITE LOOP
			} else {
				TranslateMessage(&Msg);   // translates
				DispatchMessage(&Msg);    // this line RESULTS IN
			}
		} else {
			mapConstructor->refreshEditLayer();
			tempgingerbeards->checkForInput();
			int xplay, yplay;
			firstPlayer->playerPossition(&xplay, &yplay);
			mapConstructor->mapViewPort(xplay, yplay);
			oneMob->mobMovement(refMap, firstPlayer);
			firstPlayer->draw(refMap);
			mapConstructor->getStrInChar(textToBePrinted);
			tempgingerbeards->draw(window);
		}
		Sleep(32);

	}

	return Msg.wParam;
}

void GingerBeards::draw(HWND window) {
	RECT rect;
	HDC wdc = GetDC(window);
	GetClientRect(window, &rect);
	SetTextColor(wdc, 0x00000000);
	rect.left = 40;
	rect.top = 10;
	// font size based on device units
	HFONT hf = CreateFont(lfHeight, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0,
				"Consolas");
	HFONT oldFont = (HFONT) SelectObject(wdc, hf);
	DrawText(wdc, textToBePrinted, STR_IN_CHAR_LENGTH, &rect,
	DT_NOCLIP);
	SelectObject(wdc, oldFont);
	DeleteObject (hf);
	ReleaseDC(window, wdc);
}

void GingerBeards::checkForInput() {
	Map*& refMap = mapConstructor;
	if (GetAsyncKeyState( VK_UP)) {
		firstPlayer->playerMovement(3, refMap);
	} else if (GetAsyncKeyState( VK_DOWN)) {
		firstPlayer->playerMovement(4, refMap);
	} else if (GetAsyncKeyState( VK_RIGHT)) {
		firstPlayer->playerMovement(2, refMap);
	} else if (GetAsyncKeyState( VK_LEFT)) {
		firstPlayer->playerMovement(1, refMap);
	} else {
		firstPlayer->playerMovement(5, refMap);
	}
}

void GingerBeards::mapFirstRefresh() {
	mapConstructor->mapInstantiation();
	mapConstructor->borderInstantion();
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
