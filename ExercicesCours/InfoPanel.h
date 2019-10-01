#pragma once

#ifndef DEF_INFOPANEL
#define DEF_INFOPANEL

#include "LootObject.h"
#include "InfoLine.h"

#include <string>
#include <list>

struct Panel {
	int origX;
	int origY;

	std::list<InfoLine *> text;
	int defaultColor;
	int defaultHighlight;
	InfoLine *header;

	void clear() {
		for (InfoLine* InfoLine : text) {
			delete InfoLine;
		}

		text.clear();
	}
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

	InfoLine *highlightedLine;
	int oldColorHighlightedLine;

	inline struct Panel GetDescriptionPanel() const { return descriptionPanel; }

	void HighlightLineAtCoords(int x, int y);
	void RemoveHighlight();

	void SetDescription(std::string str);
	void SetInventory(std::list<LootObject *> inventory);
};

#endif
