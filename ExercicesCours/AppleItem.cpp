#include "pch.h"
#include "AppleItem.h"
#include "GameManager.h"
#include "AppleSaladCraftableItem.h"


AppleItem::AppleItem()
{
	name = "apple";
	description = "a red apple (+" + std::to_string(heal) + " health, +" + std::to_string(food) + " food)";
	GameManager::Instance().UnlockCraft(new AppleSaladCraftableItem());
}


AppleItem::~AppleItem()
{
}

void AppleItem::OnUse()
{
	bool hasHealed = GameManager::Instance().GetPlayer()->Heal(heal);
	bool hasEaten = GameManager::Instance().GetPlayer()->Eat(food);

	if (hasEaten || hasHealed) {
		GameManager::Instance().RemoveItemFromInventory(this);
	}
}