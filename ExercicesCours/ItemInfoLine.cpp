#include "pch.h"
#include "ItemInfoLine.h"
#include "ScreenManager.h"


ItemInfoLine::ItemInfoLine(std::string _text, int _color, std::list<LootObject *> _lootObjects)
	:InfoLine(_text, _color), lootObjects(_lootObjects)
{
}


ItemInfoLine::~ItemInfoLine()
{
}

void ItemInfoLine::OnClick()
{
	lootObjects.front()->OnUse();
}

void ItemInfoLine::OnHighlight()
{
	ScreenManager::instance().SetDescription(lootObjects.front()->GetDescription());
}