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
	if(ScreenManager::instance().GetTextCoord(posX - 1, posY + 1) != 'M' && !GameManager::instance().GetGameObjectColliderAtCoordsOnMap(posX - 1, posY))
		posX--;
}

void Player::MoveRight() {
	if (ScreenManager::instance().GetTextCoord(posX + sprite.width + 1, posY + 1) != 'M' && !GameManager::instance().GetGameObjectColliderAtCoordsOnMap(posX + sprite.width + 1, posY))
		posX++;
}

void Player::MoveUp() {
	if (ScreenManager::instance().GetTextCoord(posX, posY) != 'M' && !GameManager::instance().GetGameObjectColliderAtCoordsOnMap(posX, posY - sprite.height))
		posY--;
}

void Player::MoveDown() {
	if (ScreenManager::instance().GetTextCoord(posX, posY + 1 + sprite.height) != 'M' && !GameManager::instance().GetGameObjectColliderAtCoordsOnMap(posX, posY + sprite.height))
		posY++;
}