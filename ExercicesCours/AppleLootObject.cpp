#include "pch.h"
#include "AppleLootObject.h"
#include "GameManager.h"


AppleLootObject::AppleLootObject(int x, int y, std::string spriteFile, std::string mapLink)
	: LootObject(x, y, spriteFile, mapLink)
{
	name = "apple";
	description = "a red apple (+" + std::to_string(heal) + " health, +" + std::to_string(food) + " food)";
}


AppleLootObject::~AppleLootObject()
{
}

void AppleLootObject::OnUse()
{
	bool hasHealed = GameManager::instance().GetPlayer()->Heal(heal);
	bool hasEaten = GameManager::instance().GetPlayer()->Eat(food);

	if (hasEaten || hasHealed) {
		GameManager::instance().RemoveLootFromInventory(this);
	}
}