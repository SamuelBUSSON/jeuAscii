#include "pch.h"
#include "AppleSaladItem.h"
#include "GameManager.h"


AppleSaladItem::AppleSaladItem()
{
	name = "apple salad";
	description = "it's just a couple of sliced apples (+" + std::to_string(AppleSaladItem::heal) + " health, +" + std::to_string(AppleSaladItem::food) + " food)";
}


AppleSaladItem::~AppleSaladItem()
{
}

void AppleSaladItem::OnUse()
{
	bool hasHealed = GameManager::Instance().GetPlayer()->Heal(heal);
	bool hasEaten = GameManager::Instance().GetPlayer()->Eat(food);

	if (hasEaten || hasHealed) {
		GameManager::Instance().RemoveItemFromInventory(this);
	}
}