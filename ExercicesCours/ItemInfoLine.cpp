#include "pch.h"
#include "ItemInfoLine.h"
#include "ScreenManager.h"


ItemInfoLine::ItemInfoLine(std::string _text, int _color, std::list<Item *> _items)
	:InfoLine(_text, _color), items(_items)
{
}


ItemInfoLine::~ItemInfoLine()
{
}

void ItemInfoLine::OnClick()
{
	items.front()->OnUse();
}

void ItemInfoLine::OnHighlight()
{
	ScreenManager::instance().SetDescription(items.front()->GetDescription());
}