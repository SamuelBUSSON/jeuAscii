#include "pch.h"
#include "Player.h"
#include "ScreenManager.h"
#include "GameManager.h"


Player::Player(int x, int y, std::string spriteFile)
: GameObject(x, y, spriteFile) {
	health = MAX_HEALTH - 6;
	food = MAX_FOOD + FOOD_BONUS - 12;
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


/* STATS */

//Redonne de la vie  ; si sa vie est déjà au maximum retourne faux (sinon vrai)
bool Player::Heal(int healValue)
{
	if (health == MAX_HEALTH) return false;

	health += healValue;
	if (health > MAX_HEALTH) health = MAX_HEALTH;

	ScreenManager::instance().SetHealthBarValue(GetHealth());

	return true;
}

//Remonte le niveau de nourriture ; si sa satiete est déjà au maximum retourne faux (sinon vrai)
bool Player::Eat(int foodValue)
{
	if (food == MAX_FOOD + FOOD_BONUS) return false;

	food += foodValue;
	if (food > MAX_FOOD + FOOD_BONUS) food = MAX_FOOD + FOOD_BONUS;

	ScreenManager::instance().SetFoodBarValue(GetFood());

	return true;
}