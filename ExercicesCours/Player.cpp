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
	if (ScreenManager::Instance().GetTextCoord(posX - sprite.width / 2, posY + sprite.height) != 'M' && !GameManager::Instance().GetGameObjectColliderAtCoordsOnMap(posX - 1, posY + sprite.height))
	{
		SetX(posX - 1);
	}
}

void Player::MoveRight() {
	if (ScreenManager::Instance().GetTextCoord(posX + sprite.width, posY + sprite.height) != 'M' && !GameManager::Instance().GetGameObjectColliderAtCoordsOnMap(posX + sprite.width, posY + sprite.height))
	{
		SetX(posX + 1);
	}
}

void Player::MoveUp() {
	if (ScreenManager::Instance().GetTextCoord(posX + sprite.width / 2, posY + sprite.height - 1) != 'M' && !GameManager::Instance().GetGameObjectColliderAtCoordsOnMap(posX + sprite.width / 2, posY - sprite.height + sprite.height))
	{
		SetY(posY - 1);
	}
}

void Player::MoveDown() {
	if (ScreenManager::Instance().GetTextCoord(posX + sprite.width / 2, posY + 1 + sprite.height) != 'M' && !GameManager::Instance().GetGameObjectColliderAtCoordsOnMap(posX + sprite.width / 2, posY + sprite.height + sprite.height)) {
		SetY(posY + 1);
	}
}


/* STATS */

//Redonne de la vie  ; si sa vie est déjà au maximum retourne faux (sinon vrai)
bool Player::Heal(int healValue)
{
	if (health == MAX_HEALTH) return false;

	health += healValue;
	if (health > MAX_HEALTH) health = MAX_HEALTH;

	ScreenManager::Instance().SetHealthBarValue(GetHealth());

	return true;
}

//Perdre de la vie  ; si sa vie est déjà à 0 retourne faux (sinon vrai)
bool Player::GetDammage(int dammageValue)
{
	if (health == 0) return false;

	health -= dammageValue;

	if (health < 0) health = 0;

	ScreenManager::Instance().SetHealthBarValue(GetHealth());

	return true;
}

//Remonte le niveau de nourriture ; si sa satiete est déjà au maximum retourne faux (sinon vrai)
bool Player::Eat(int foodValue)
{
	if (food == MAX_FOOD + FOOD_BONUS) return false;

	food += foodValue;
	if (food > MAX_FOOD + FOOD_BONUS) food = MAX_FOOD + FOOD_BONUS;

	ScreenManager::Instance().SetFoodBarValue(GetFood());

	return true;
}

bool Player::LooseFood(int foodValue)
{
	if (food == 0) {
		GetDammage(1);
		return false;
	}

	food -= foodValue;
	ScreenManager::Instance().SetFoodBarValue(GetFood());
	return true;
}
