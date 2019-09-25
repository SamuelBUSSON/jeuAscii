#include "pch.h"
#include "Player.h"
#include "ScreenManager.h"
#include "GameManager.h"


Player::Player(int x, int y, std::string spriteFile)
: GameObject(x, y, spriteFile) {
	health = PLAYER_HEALTH;
	food = PLAYER_FOOD;
}


Player::~Player() {
}

void Player::MoveLeft() {
	if(ScreenManager::instance().GetTextCoord(posX - 1, posY) != 'M' && !GameManager::instance().GetGameObjectAtCoords(posX - 1, posY))
		posX--;
}

void Player::MoveRight() {
	if (ScreenManager::instance().GetTextCoord(posX + sprite.width, posY) != 'M' && !GameManager::instance().GetGameObjectAtCoords(posX + sprite.width + 1, posY))
		posX++;
}

void Player::MoveUp() {
	if (ScreenManager::instance().GetTextCoord(posX, posY - 1) != 'M' && !GameManager::instance().GetGameObjectAtCoords(posX, posY - 1))
		posY--;
}

void Player::MoveDown() {
	if (ScreenManager::instance().GetTextCoord(posX, posY + sprite.height) != 'M' && !GameManager::instance().GetGameObjectAtCoords(posX, posY + sprite.height + 1))
		posY++;
}