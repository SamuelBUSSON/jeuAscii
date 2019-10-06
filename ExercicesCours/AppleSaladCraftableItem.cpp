#include "pch.h"
#include "AppleSaladCraftableItem.h"
#include "AppleSaladItem.h"
#include "GameManager.h"
#include "AppleItem.h"
#include "RockItem.h"

AppleSaladCraftableItem::AppleSaladCraftableItem()
{
	name = "apple salad";
	description = "it's just a couple of sliced apples (+" + std::to_string(AppleSaladItem::heal) + " health, +" + std::to_string(AppleSaladItem::food) + " food)";
}


AppleSaladCraftableItem::~AppleSaladCraftableItem()
{
}

void AppleSaladCraftableItem::OnUnlock()
{

	itemsNeededToCraft.push_back(new AppleItem());
	itemsNeededToCraft.push_back(new AppleItem());
	itemsNeededToCraft.push_back(new AppleItem());

	AppendDescriptionWithNeededItems();
}

void AppleSaladCraftableItem::OnUse()
{
	GameManager::instance().Craft(this);
}

std::list<Item *> AppleSaladCraftableItem::GetItemsToCraft() 
{
	return std::list<Item *>({
		new AppleSaladItem() 
	}); 
}