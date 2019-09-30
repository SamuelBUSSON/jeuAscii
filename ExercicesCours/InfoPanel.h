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

	void clear() {
		for (Line* line : text) {
			delete line;
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

	Line *highlightedLine;
	int oldColorHighlightedLine;

	inline struct Panel GetDescriptionPanel() const { return descriptionPanel; }

	void HighlightLineAtCoords(int x, int y);
	void RemoveHighlight();

	void SetDescription(std::string str);
	void SetInventory(std::list<LootObject *> inventory);
};

#endif
