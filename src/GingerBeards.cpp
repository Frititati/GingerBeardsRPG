#include "gingerbeards.h"
#include "player.h"
#include "mobcontrol.h"
#include <iostream>
#include <fstream>
#include "Menu.h"

using namespace std;

const char g_szClassName[] = "myWindowClass";

Menu* menu = new Menu();
Map* mapConstructor;
GingerBeards* tempgingerbeards = new GingerBeards();
Player* firstPlayer;
Mob* boss;
MobControl* mobs;

bool isGameRunning = false;

char textToBePrinted[STR_IN_CHAR_LENGTH];

long lfHeight = tempgingerbeards->computeFontHeight();

enum GameState {
	MAIN_MENU, IN_GAME, LOAD_GAME, THE_END, QUIT
};

enum GameState gameState = MAIN_MENU;
bool stateShift = false;

// get the height of the font based on device units
long GingerBeards::computeFontHeight() {
	HDC hdc = GetDC(NULL);
	long result = -MulDiv(FONT_SIZE, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	ReleaseDC(NULL, hdc);
	return result;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
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

HWND window;
MSG Msg;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;

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
	WS_EX_CLIENTEDGE, g_szClassName, "A Ginger Tale",
	WS_OVERLAPPEDWINDOW, 50, 100, 900, 700,
	NULL, NULL, hInstance, NULL);

	if (window == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!",
		MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(window, nCmdShow);
	UpdateWindow(window);

	while (gameState != QUIT) {
		stateShift = false;
		switch (gameState) {
		case MAIN_MENU:
			cout << "main_MAIN_MENU1" << endl;
			tempgingerbeards->menuLoop();
			break;
		case IN_GAME:
			tempgingerbeards->gameLoop();
			break;
		case THE_END:
			cout << "main_THE_END1" << endl;
			menu->endScreen(textToBePrinted);
			isGameRunning = false;
			gameState = MAIN_MENU;
			while (!stateShift && !GetAsyncKeyState(0x43)) { // c key
				cout << "main_THE_END2" << endl;
				tempgingerbeards->peekMessage();
				tempgingerbeards->draw(window);
				Sleep(MENU_DELAY_MS);
			}
		}
		Sleep(MENU_DELAY_MS);
	}

	return Msg.wParam;
}

void GingerBeards::menuLoop() {
	if (isGameRunning) {
		menu->inGame();
		menu->setMessage("Nice to see you again <3", 24);
	} else {
		menu->notInGame();
		menu->setMessage("", 0);
	}
	while (!stateShift) {
		tempgingerbeards->peekMessage();
		menu->draw();
		tempgingerbeards->checkForMenuInput();
		menu->getStrInChar(textToBePrinted);
		tempgingerbeards->draw(window);
		Sleep(MENU_DELAY_MS);
	}
}

void GingerBeards::gameLoop() {
	Map*& refMap = mapConstructor;
	while (!stateShift) {  // LOOP FOREVER
		tempgingerbeards->peekMessage();
		tempgingerbeards->checkForGameInput();
		int xplay, yplay;
		firstPlayer->playerPosition(&xplay, &yplay);
		mapConstructor->mapViewPort(xplay, yplay);
		mobs->completeAI(refMap, firstPlayer);
		firstPlayer->draw(refMap);
		firstPlayer->heal();
		cout << "GingerBeards::gameLoop1" << endl;
		boss->mobMovement(refMap, firstPlayer);
		cout << "GingerBeards::gameLoop2" << endl;
		mapConstructor->drawStatsBar(firstPlayer->getMaxHP(),
				firstPlayer->getHP(), firstPlayer->getAttackStrength(),
				firstPlayer->getDefense());
		mapConstructor->getStrInChar(textToBePrinted);
		tempgingerbeards->draw(window);
		if (boss->getHealth() < 1) {
			gameState = THE_END;
			stateShift = true;
		}
		if (firstPlayer->hasDied()) {
			isGameRunning = false;
		}
		Sleep(GAME_DELAY_MS);
	}
}

void GingerBeards::peekMessage() {
	if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
		if (Msg.message == WM_QUIT) {
			gameState = QUIT;
			stateShift = true;  // BREAK OUT OF INFINITE LOOP
		} else {
			TranslateMessage(&Msg);   // translates
			DispatchMessage(&Msg);    // this line RESULTS IN
		}
	}
}

void GingerBeards::draw(HWND window) {
	RECT rect;
	HDC wdc = GetDC(window);
	GetClientRect(window, &rect);
	SetTextColor(wdc, 0x00000000);
	rect.left = 40;
	rect.top = 10;
//	RECT recttest;
//	recttest.left = 10;
//	recttest.right = 920;
//	recttest.bottom = 320;
//	recttest.top = 10;
//	HBRUSH redbrush = (HBRUSH) CreateSolidBrush(RGB(255,0,0));
//	FillRect(wdc, &recttest, redbrush);
//	DeleteObject(redbrush);
	HFONT hf = CreateFont(lfHeight, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0,
			"Consolas");
	HFONT oldFont = (HFONT) SelectObject(wdc, hf);
	DrawText(wdc, textToBePrinted, STR_IN_CHAR_LENGTH, &rect, DT_NOCLIP);
	SelectObject(wdc, oldFont);
	DeleteObject(hf);
	ReleaseDC(window, wdc);
}

void GingerBeards::setupGame() {
	mapConstructor = new Map();
	firstPlayer = new Player();
	boss = new Mob();
	boss->createBoss(273, 18);
	mobs = new MobControl();
	tempgingerbeards->mapFirstRefresh();
	isGameRunning = true;
}

void GingerBeards::checkForMenuInput() {
	if (GetAsyncKeyState(VK_UP)) {
		menu->cursorUp();
	} else if (GetAsyncKeyState(VK_DOWN)) {
		menu->cursorDown();
	} else if (GetAsyncKeyState(0x0D)) {	// carriage return
		switch (menu->getSelectedItem()) {
		case 0:	// new game
			setupGame();
			gameState = IN_GAME;
			intro();
			stateShift = true;
			break;
		case 1:	// continue
			stateShift = true;
			gameState = IN_GAME;
			break;
		case 2: // save
			tempgingerbeards->saveGame();
			break;
		case 3: // load
			if (!tempgingerbeards->loadGame()) {
				menu->setMessage("No save file found :(", 21);
			} else {
				stateShift = true;
				gameState = IN_GAME;
			}
			break;
		case 4:
			// quit
			stateShift = true;
			gameState = QUIT;
		}
	}
}

bool GingerBeards::saveGame() {
//	if (!isGameRunning)
//		return false;
	int x, y;
	ofstream myfile;
	myfile.open("save.gb");
	firstPlayer->playerPosition(&x, &y);
//	myfile.write(reinterpret_cast<const char *>(&x), sizeof(x));
	myfile << x << endl;
	myfile << y << endl;
	myfile << firstPlayer->getAttackStrength() << endl;
	myfile << firstPlayer->getDefense() << endl;
	myfile << firstPlayer->getHP() << endl;
	myfile << firstPlayer->getMaxHP() << endl;

	menu->setMessage("Save successful ;)", 18);
	myfile.close();
	return true;
}
//Save successful ;)

void GingerBeards::intro() {
	char pages[][25] = { "instructions_page1.txt", "instructions_page2.txt",
			"instructions_page3.txt" };
	cout << "GingerBeards::checkForMenuInput1" << endl;
	for (int i = 0; i < 3; i++) {
		menu->readPage(textToBePrinted, pages[i]);
		cout << "GingerBeards::checkForMenuInput2" << endl;
		while (!GetAsyncKeyState(0x43)) {
			if (stateShift)
				return;
			peekMessage();
			tempgingerbeards->draw(window);
			Sleep(MENU_DELAY_MS);
		}
		Sleep(MENU_DELAY_MS);
	}
	cout << "GingerBeards::checkForMenuInput3" << endl;
}

bool GingerBeards::loadGame() {
	ifstream myfile;
	int x, y, attack, defense, HP, maxHP;
	myfile.open("save.gb");
	if (!myfile.is_open())
		return false;
	setupGame();
	myfile >> x;
	myfile >> y;
	myfile >> attack;
	myfile >> defense;
	myfile >> HP;
	myfile >> maxHP;
	firstPlayer->loadCharacter(x, y, attack, defense, HP, maxHP);
	menu->setMessage("Loading complete :D", 19);
	myfile.close();
	return true;
}

void GingerBeards::checkForGameInput() {
	Map*& refMap = mapConstructor;
	// movement
	if (GetAsyncKeyState(VK_UP)) {
		firstPlayer->playerMovement(3, refMap);
	} else if (GetAsyncKeyState(VK_DOWN)) {
		firstPlayer->playerMovement(4, refMap);
	} else if (GetAsyncKeyState( VK_RIGHT)) {
		firstPlayer->playerMovement(2, refMap);
	} else if (GetAsyncKeyState( VK_LEFT)) {
		firstPlayer->playerMovement(1, refMap);
	}
	if (GetAsyncKeyState(0x41)) {
		firstPlayer->setAttack(1); // a
	} else if (GetAsyncKeyState(0x53)) {
		firstPlayer->setAttack(4); // s
	} else if (GetAsyncKeyState(0x44)) {
		firstPlayer->setAttack(2); // d
	} else if (GetAsyncKeyState(0x57)) {
		firstPlayer->setAttack(3); // w
	} else if (GetAsyncKeyState(0x51)) {
		firstPlayer->setAttack(5); // q
	} else if (GetAsyncKeyState(0x4D)) {
		stateShift = true;			// m
		gameState = MAIN_MENU;
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
