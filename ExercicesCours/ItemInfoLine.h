#pragma once
#include "InfoLine.h"
#include "LootObject.h"
#include <list>

class ItemInfoLine : public InfoLine
{
private:
	std::list<LootObject *> lootObjects;

public:
	ItemInfoLine(std::string _text, int _color, std::list<LootObject *> _lootObjects);
	~ItemInfoLine();

	void OnClick() override;
	void OnHighlight() override;
};

