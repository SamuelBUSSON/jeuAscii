#pragma once

#ifndef DEF_INFOPANEL
#define DEF_INFOPANEL

#include "LootObject.h"
#include "InfoLine.h"

#include <string>
#include <list>

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

class InfoPanel
{
private:
	
	struct Panel descriptionPanel;
	struct Panel inventoryPanel;

public:
	InfoPanel();
	~InfoPanel();

	std::list<struct Panel *> panels;

	int defaultHighlight = 0x05;
	InfoLine *highlightedLine;
	int oldColorHighlightedLine;

	inline struct Panel GetDescriptionPanel() const { return descriptionPanel; }


	InfoLine *FindLineAtCoords(int x, int y);
	void HighlightLineAtCoords(int x, int y);
	void RemoveHighlight();
	void ClickOnCoords(int x, int y);

	void SetDescription(std::string str);
	void SetInventory(std::list<LootObject *> inventory);
};

#endif
