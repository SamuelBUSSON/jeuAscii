#pragma once

#ifndef DEF_INFOPANEL
#define DEF_INFOPANEL

#include "LootObject.h"

#include <string>
#include <list>

struct Panel {
	int origX;
	int origY;
	std::list<std::string> text;
	int color;
	std::string header;
	int headerColor;
};

class InfoPanel
{
private:
	
	struct Panel descriptionPanel;
	struct Panel inventoryPanel;

public:
	InfoPanel();
	~InfoPanel();

	std::list<struct Panel *> panels;

	inline void SetDescription(std::string str) { descriptionPanel.text.clear(); descriptionPanel.text.push_front(str); }

	inline struct Panel GetDescriptionPanel() const { return descriptionPanel; }

	inline void SetInventory(std::list<LootObject *> inventory) { inventoryPanel.text.clear(); for (LootObject *loot : inventory) inventoryPanel.text.push_back("+ " + loot->GetName()); }
};

#endif
