#include "pch.h"
#include "Player.h"
#include "ScreenManager.h"
#include "GameManager.h"


Player::Player(int x, int y, std::string spriteFile)
: GameObject(x, y, spriteFile) {
	health = PLAYER_HEALTH;
	food = PLAYER_FOOD;
	description = "It's you !";
}


Player::~Player() {
}

void Player::MoveLeft() {
	if (ScreenManager::instance().GetTextCoord(posX - sprite.width / 2, posY + sprite.height) != 'M' && !GameManager::Instance().GetGameObjectColliderAtCoordsOnMap(posX - 1, posY + sprite.height))
	{
		SetX(posX - 1);
	}
}

void Player::MoveRight() {
	if (ScreenManager::instance().GetTextCoord(posX + sprite.width, posY + sprite.height) != 'M' && !GameManager::Instance().GetGameObjectColliderAtCoordsOnMap(posX + sprite.width, posY + sprite.height)) 
	{
		SetX(posX + 1);
	}
}

void Player::MoveUp() {
	if (ScreenManager::instance().GetTextCoord(posX + sprite.width / 2, posY + sprite.height - 1) != 'M' && !GameManager::Instance().GetGameObjectColliderAtCoordsOnMap(posX + sprite.width / 2, posY - sprite.height + sprite.height))
	{
		SetY(posY - 1);
	}
}

void Player::MoveDown() {
	if (ScreenManager::instance().GetTextCoord(posX + sprite.width / 2, posY + 1 + sprite.height) != 'M' && !GameManager::Instance().GetGameObjectColliderAtCoordsOnMap(posX + sprite.width / 2, posY + sprite.height + sprite.height))
	{
		SetY(posY + 1);
	}
}