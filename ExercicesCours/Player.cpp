#include "pch.h"
#include "Player.h"
#include "ScreenManager.h"
#include "GameManager.h"


Player::Player(int x, int y, std::string spriteFile)
: GameObject(x, y, spriteFile) {
	health = PLAYER_MAX_HEALTH - 6;
	food = PLAYER_MAX_FOOD;
	description = "it's you !";
}


Player::~Player() {
}

void Player::MoveLeft() {
	if(ScreenManager::instance().GetTextCoord(posX - sprite.width / 2, posY + sprite.height) != 'M' && !GameManager::instance().GetGameObjectColliderAtCoordsOnMap(posX - 1, posY + sprite.height))
		posX--;
}

void Player::MoveRight() {
	if (ScreenManager::instance().GetTextCoord(posX + sprite.width, posY + sprite.height) != 'M' && !GameManager::instance().GetGameObjectColliderAtCoordsOnMap(posX + sprite.width, posY + sprite.height))
		posX++;
}

void Player::MoveUp() {
	if (ScreenManager::instance().GetTextCoord(posX + sprite.width / 2, posY + sprite.height - 1) != 'M' && !GameManager::instance().GetGameObjectColliderAtCoordsOnMap(posX + sprite.width/2, posY - sprite.height + sprite.height))
		posY--;
}

void Player::MoveDown() {
	if (ScreenManager::instance().GetTextCoord(posX + sprite.width / 2, posY + 1 + sprite.height) != 'M' && !GameManager::instance().GetGameObjectColliderAtCoordsOnMap(posX + sprite.width / 2, posY + sprite.height + sprite.height))
		posY++;
}

//Redonne de la vie  ; si sa vie est déjà au maximum retourne faux (sinon vrai)
bool Player::Heal(int healValue)
{
	if (health == PLAYER_MAX_HEALTH) return false;

	health += healValue;
	if (health > PLAYER_MAX_HEALTH) health = PLAYER_MAX_HEALTH;

	return true;
}