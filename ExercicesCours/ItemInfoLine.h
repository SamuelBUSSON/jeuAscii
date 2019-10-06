#pragma once
#include "InfoLine.h"
#include "Item.h"
#include <list>

class ItemInfoLine : public InfoLine
{
private:
	std::list<Item *> items;

public:
	ItemInfoLine(std::string _text, int _color, std::list<Item *> _items);
	~ItemInfoLine();

	void OnClick() override;
	void OnHighlight() override;
};

