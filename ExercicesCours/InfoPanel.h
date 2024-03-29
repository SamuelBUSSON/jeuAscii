#pragma once

#ifndef DEF_INFOPANEL
#define DEF_INFOPANEL

#include "Item.h"
#include "InfoLine.h"
#include "CraftableItem.h"

#include <string>
#include <list>

//TODO faire de ceci une classe
struct Panel {
	int marginX;
	int marginY;

	std::list<InfoLine *> text;
	int defaultColor = 0x08;
	InfoLine *header;

	int padding = 0;

	void clear() {
		for (InfoLine* InfoLine : text) {
			delete InfoLine;
		}

		text.clear();
	}
};

struct TextBar {
	int origX;
	int origY;
	InfoLine *label;
	unsigned int value;
	unsigned int maxValue;
	int color;
	char unit = ' ';
};

class InfoPanel
{
private:
	
	struct Panel descriptionPanel;
	struct Panel inventoryPanel;
	struct Panel craftPanel;

public:
	InfoPanel();
	~InfoPanel();

	std::list<struct Panel *> panels;
	struct TextBar healthBar;
	struct TextBar foodBar;


	int defaultHighlight = 0x05;
	InfoLine *highlightedLine;
	int oldColorHighlightedLine;

	inline struct Panel GetDescriptionPanel() const { return descriptionPanel; }


	InfoLine *FindLineAtCoords(int x, int y);
	void HighlightLineAtCoords(int x, int y);
	void RemoveHighlight();
	void ClickOnCoords(int x, int y);

	void SetDescription(std::string str);
	void SetInventory(std::list<Item *> inventory);
	void SetCrafts(std::list<CraftableItem *> items);
};

#endif
