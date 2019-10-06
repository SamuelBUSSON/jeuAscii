#include "pch.h"
#include "AppleSaladItem.h"
#include "GameManager.h"
#include "AppleItem.h"
#include "RockItem.h"

AppleSaladItem::AppleSaladItem()
{
	name = "apple salad";
	description = "it's just a couple of sliced apples (+" + std::to_string(heal) + " health, +" + std::to_string(food) + " food)";
}


AppleSaladItem::~AppleSaladItem()
{
}

void AppleSaladItem::OnUnlock()
{

	itemsNeededToCraft.push_back(new AppleItem());
	itemsNeededToCraft.push_back(new AppleItem());
	itemsNeededToCraft.push_back(new AppleItem());
	itemsNeededToCraft.push_back(new RockItem());

	AppendDescriptionWithNeededItems();
}

void AppleSaladItem::OnCraft()
{
	GameManager::instance().AddItemToInventory(this);
}
