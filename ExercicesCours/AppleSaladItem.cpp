#include "pch.h"
#include "AppleSaladItem.h"
#include "GameManager.h"

AppleSaladItem::AppleSaladItem()
{
	name = "apple salad";
	description = "it's just a couple of sliced apples (+" + std::to_string(heal) + " health, +" + std::to_string(food) + " food)";
}


AppleSaladItem::~AppleSaladItem()
{
}

void AppleSaladItem::OnCraft()
{
	GameManager::instance().AddItemToInventory(this);
}
