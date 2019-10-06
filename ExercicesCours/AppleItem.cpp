#include "pch.h"
#include "AppleItem.h"
#include "GameManager.h"


AppleItem::AppleItem()
{
	name = "apple";
	description = "a red apple (+" + std::to_string(heal) + " health, +" + std::to_string(food) + " food)";
}


AppleItem::~AppleItem()
{
}

void AppleItem::OnUse()
{
	bool hasHealed = GameManager::instance().GetPlayer()->Heal(heal);
	bool hasEaten = GameManager::instance().GetPlayer()->Eat(food);

	if (hasEaten || hasHealed) {
		GameManager::instance().RemoveItemFromInventory(this);
	}
}