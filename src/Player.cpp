/*
 * Player.cpp
 *
 *  Created on: 25.04.2016
 *      Author: Michele
 */

#include "Player.h"

Player::Player(int startx, int starty, char portrait[]) {
	x = startx;
	y = starty;
	xSpeed = 4;
	ySpeed = 4;
//	this->portrait = portrait;
}

bool Player::moveRight() {
	x += xSpeed;
	return true;
}

bool Player::moveLeft() {
	x -= xSpeed;
	return true;
}

bool Player::moveUp() {
	y -= ySpeed;
	return true;
}

bool Player::moveDown() {
	y += ySpeed;
	return true;
}

Player::~Player() {
	delete portrait;
}

