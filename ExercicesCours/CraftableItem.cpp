#include "pch.h"
#include "CraftableItem.h"
#include "GameManager.h"
#include <map>

CraftableItem::CraftableItem()
	:Item()
{
	itemsNeededToCraft = std::list<Item *>();
}


CraftableItem::~CraftableItem()
{
	for (Item *item : itemsNeededToCraft) {
		delete item;
	}
}

void CraftableItem::OnUnlock()
{
}

void CraftableItem::AppendDescriptionWithNeededItems()
{
	if (itemsNeededToCraft.size() > 0) {
		description += " ; needs ";

		std::map<std::string, std::list<Item*>> countItems;
		for (Item *item : itemsNeededToCraft) {
			countItems[item->GetName()].push_back(item);
		}

		size_t count = 0;
		for (std::pair<std::string, std::list<Item*>> item : countItems) {
			description += item.first + " x" + std::to_string(item.second.size()) + (count < countItems.size() - 1 ? ", " : "");
			count++;
		}

		description += " to make";
	}
}