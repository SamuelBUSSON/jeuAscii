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
}

void ItemInfoLine::OnHighlight()
{
	ScreenManager::instance().SetDescription(lootObject->GetDescription());
}

void ItemInfoLine::OnLeaveHighlight()
{
	ScreenManager::instance().SetDescription("");
}