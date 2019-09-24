#include "pch.h"
#include "Player.h"


Player::Player() {
}


Player::~Player() {
}

void Player::MoveLeft() {
	posX--;
}

void Player::MoveRight() {
	posX++;
}

void Player::MoveUp() {
	posY--;
}

void Player::MoveDown() {
	posY++;
}