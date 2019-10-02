#include "pch.h"
#include "ItemInfoLine.h"
#include "ScreenManager.h"


ItemInfoLine::ItemInfoLine(std::string _text, int _color, LootObject *_lootObject)
	:InfoLine(_text, _color), lootObject(_lootObject)
{
}


ItemInfoLine::~ItemInfoLine()
{
}

void ItemInfoLine::OnClick()
{
	lootObject->OnUse();
}

void ItemInfoLine::OnHighlight()
{
	ScreenManager::instance().SetDescription(lootObject->GetDescription());
}