#include "pch.h"
#include "Player.h"


Player::Player(int x, int y)
: GameObject(x, y) {

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