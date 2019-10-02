#pragma once
#include "InfoLine.h"
#include "LootObject.h"

class ItemInfoLine : public InfoLine
{
private:
	LootObject *lootObject;

public:
	ItemInfoLine(std::string _text, int _color, LootObject *_lootObject);
	~ItemInfoLine();

	void OnClick() override;
	void OnHighlight() override;
};

