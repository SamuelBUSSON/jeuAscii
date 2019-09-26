#pragma once

#ifndef DEF_INFOPANEL
#define DEF_INFOPANEL

#include "LootObject.h"

#include <string>
#include <list>

struct Line {
	std::string text;
	int color;
};

struct Panel {
	int origX;
	int origY;

	std::list<struct Line *> text;
	int defaultColor;
	struct Line header;
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

	void HighlightLineAtCoords(int x, int y);

	void SetInventory(std::list<LootObject *> inventory);
};

#endif
