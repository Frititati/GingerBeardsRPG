/*
 * Menu.h
 *
 *  Created on: 26.05.2016
 *      Author: Michele
 */

#ifndef SRC_MENU_H_
#define SRC_MENU_H_

const int MESSAGE_Y = (VIEWPORT_HEIGHT / 4) * 3;
const int MENU_DELAY_MS = 128;
const int MSG_COUNTDOWN_SECONDS = 5;
const int MSG_COUNTDOWN_FRAMES = MSG_COUNTDOWN_SECONDS * (1000 / MENU_DELAY_MS);

class Menu {
public:
	Menu();
	void draw();
	void getStrInChar(char*);
	void cursorUp();
	void cursorDown();
	int getSelectedItem();
	void setMessage(char*, int);
	void inGame();
	void notInGame();
	void endScreen(char*);
	void instructionsScreen(char*);
private:
	void clearScreen();
	void drawOptions();
	int cursor;
	char* message;
	int messageLength;
	int numberOfOptions;
	int topmostOption;
	int* codes;
};



#endif /* SRC_MENU_H_ */
