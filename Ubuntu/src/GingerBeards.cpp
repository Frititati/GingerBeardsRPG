#include "GingerBeards.h"
#include "Player.h"
#include "MobControl.h"
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <unistd.h>
using namespace std;


Map* mapConstructor = new Map();
GingerBeards* tempgingerbeards = new GingerBeards();
Player* firstPlayer = new Player();
MobControl* mobs = new MobControl();

int main() {
	initscr();
	raw();
	nodelay(stdscr,TRUE);
	noecho();
	curs_set(FALSE);
	tempgingerbeards->mapFirstRefresh();
	Map*& refMap = mapConstructor;
	while (tempgingerbeards->checkForInput()) {  // LOOP FOREVER
		int xplay, yplay;
		firstPlayer->playerPossition(&xplay, &yplay);
		mapConstructor->mapViewPort(xplay, yplay);
		mobs->completeAI(refMap, firstPlayer);
		firstPlayer->draw(refMap);
		mapConstructor->draw();
		usleep(32000);
	}
	endwin();
	return 0;
}

bool GingerBeards::checkForInput() {
	Map*& refMap = mapConstructor;
	int input;
	bool alreadyMoved = false;
	bool alreadyAttacked = false;
	while ((input = getch()) != -1) {
		if (!alreadyMoved) {
			if (input == 65) { // UP
				firstPlayer->playerMovement(3, refMap);
				alreadyMoved = true;
			} else if (input == 66) { // DOWN
				firstPlayer->playerMovement(4, refMap);
				alreadyMoved = true;
			} else if (input == 67) { // RIGHT
				firstPlayer->playerMovement(2, refMap);
				alreadyMoved = true;
			} else if (input == 68) { // LEFT
				firstPlayer->playerMovement(1, refMap);
				alreadyMoved = true;
			}
		}
		if (!alreadyAttacked) {
			if (input == 'a') {
				firstPlayer->setAttack(1); // a
				alreadyAttacked = true;
			} else if (input == 's') {
				firstPlayer->setAttack(4); // s
				alreadyAttacked = true;
			} else if (input == 'd') {
				firstPlayer->setAttack(2); // d
				alreadyAttacked = true;
			} else if (input == 'w') {
				firstPlayer->setAttack(3);// w
				alreadyAttacked = true;
			} else if (input == 'q') {
				firstPlayer->setAttack(5);
				alreadyAttacked = true;
			} 
		}
		if (input == 't')
			return false;
	}
	return true;
}

void GingerBeards::mapFirstRefresh() {
	mapConstructor->mapInstantiation();
	mapConstructor->borderInstantion();
}
