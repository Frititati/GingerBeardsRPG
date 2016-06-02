/*
 * Menu.cpp
 *
 *  Created on: 26.05.2016
 *      Author: Michele
 */

#include "Map.h"
#include "Menu.h"
#include <iostream>

using namespace std;

char** options;
int* optionsLength;
char screen[VIEWPORT_HEIGHT][VIEWPORT_WIDTH];
int msgCountDown;

Menu::Menu() {
	cursor = 0;
	message = "";
	messageLength = 0;
	msgCountDown = MSG_COUNTDOWN_FRAMES;
}

void Menu::inGame() {
	cursor = 0;
	numberOfOptions = 5;
	topmostOption = VIEWPORT_HEIGHT / 2 - 2;
	optionsLength = new int[5];
	options = new char *[5];
	codes = new int[5];
	options[0] = "New Game";
	options[1] = "Continue";
	options[2] = "Save";
	options[3] = "Load";
	options[4] = "Quit";
	optionsLength[0] = 8;
	optionsLength[1] = 8;
	optionsLength[2] = 4;
	optionsLength[3] = 4;
	optionsLength[4] = 4;
	for (int i = 0; i < 5; i++) {
		codes[i] = i;
	}
}

void Menu::notInGame() {
	cursor = 0;
	numberOfOptions = 3;
	topmostOption = VIEWPORT_HEIGHT / 2 - 1;
	options = new char *[3];
	optionsLength = new int[3];
	codes = new int[3];
	options[0] = "New Game";
	options[1] = "Load";
	options[2] = "Quit";
	optionsLength[0] = 8;
	optionsLength[1] = 4;
	optionsLength[2] = 4;
	codes[0] = 0;
	codes[1] = 3;
	codes[2] = 4;
}

void Menu::draw() {
	this->clearScreen();
	this->drawOptions();
	// draw the cursor
	screen[topmostOption + cursor][VIEWPORT_WIDTH / 2
			- optionsLength[cursor] / 2 - 1] = '>';

	// draw message
	if (msgCountDown > 0) {
		for (int i = 0, j = VIEWPORT_WIDTH / 2 - messageLength / 2;
				i < messageLength; i++, j++) {
			screen[MESSAGE_Y][j] = message[i];
		}
		msgCountDown--;
	}
}

void Menu::cursorUp() {
	if (cursor > 0) {
		cursor--;
	}
}

void Menu::cursorDown() {
	if (cursor < numberOfOptions - 1) {
		cursor++;
	}
}

void Menu::getStrInChar(char* strInChar) {
	for (int i = 0, charAt = 0; i < VIEWPORT_HEIGHT; i++, charAt++) {
		for (int j = 0; j < VIEWPORT_WIDTH; j++, charAt++) {
			strInChar[charAt] = screen[i][j];
		}
		strInChar[charAt] = '\n';
	}
}

void Menu::setMessage(char* message, int length) {
	this->message = message;
	messageLength = length;
	msgCountDown = MSG_COUNTDOWN_FRAMES;
}

int Menu::getSelectedItem() {
	return codes[cursor];
}

void Menu::endScreen(char* strInChar) {
	numberOfOptions = 11;
	topmostOption = VIEWPORT_HEIGHT / 2 - numberOfOptions / 2;
	optionsLength = new int[numberOfOptions];
	options = new char *[numberOfOptions];
	options[0] = "The End.";
	options[1] = "";
	options[2] = "Thank you for playing!";
	options[3] = "";
	options[4] = "@The authors:";
	options[5] = "";
	options[6] = "Filippo Cardano";
	options[7] = "Marco Brillo";
	options[8] = "Michele Pettinato";
	options[9] = "";
	options[10] = "Press 'c' to continue";
	optionsLength[0] = 8;
	optionsLength[1] = 0;
	optionsLength[2] = 22;
	optionsLength[3] = 0;
	optionsLength[4] = 13;
	optionsLength[5] = 0;
	optionsLength[6] = 15;
	optionsLength[7] = 12;
	optionsLength[8] = 17;
	optionsLength[9] = 0;
	optionsLength[10] = 21;
	cout << "Menu::endScreen1" << endl;
	clearScreen();
	cout << "Menu::endScreen1.1" << endl;
	drawOptions();
	cout << "Menu::endScreen2" << endl;
	getStrInChar(strInChar);
}

void Menu::clearScreen() {
	for (int i = 0; i < VIEWPORT_HEIGHT; i++) {
		for (int j = 0; j < VIEWPORT_WIDTH; j++) {
			screen[i][j] = ' ';
		}
	}
}

void Menu::drawOptions() {
	for (int i = topmostOption, ki = 0; ki < numberOfOptions; ki++, i++) {
		int length = optionsLength[ki];
		for (int j = VIEWPORT_WIDTH / 2 - length / 2, kj = 0; kj < length;
				kj++, j++) {
			screen[i][j] = options[ki][kj];
		}
	}
}

