#include "pch.h"
#include "InfoPanel.h"

#include <map>
#include <iostream>


InfoPanel::InfoPanel()
{
	descriptionPanel.origX = 0;
	descriptionPanel.origY = 0;
	descriptionPanel.defaultColor = 0x08;
	descriptionPanel.defaultHighlight = 0x05;
	descriptionPanel.header.color = 0x07;
	descriptionPanel.header.text = "Description :";
	struct Line *emptyLine = new struct Line({ "", descriptionPanel.defaultColor });
	descriptionPanel.text.push_back(emptyLine);
	panels.push_back(&descriptionPanel);

	inventoryPanel.origX = 0;
	inventoryPanel.origY = 3;
	inventoryPanel.defaultColor = 0x08;
	inventoryPanel.defaultHighlight = 0x05;
	inventoryPanel.header.color = 0x07;
	inventoryPanel.header.text = "Inventory :";
	panels.push_back(&inventoryPanel);

	highlightedLine = nullptr;
	oldColorHighlightedLine = 0;
}


InfoPanel::~InfoPanel()
{
	for (Panel* panel : panels)
	{
		panel->clear();
	}
}


void InfoPanel::SetDescription(std::string str)
{ 
	descriptionPanel.clear();

	struct Line *newLine = new struct Line({ str, descriptionPanel.defaultColor });
	descriptionPanel.text.push_front(newLine);
}


void InfoPanel::SetInventory(std::list<LootObject *> inventory) {
	inventoryPanel.clear();
	std::map<std::string, int> countNames;
	for (LootObject *loot : inventory) {
		countNames[loot->GetName()]++;
	}

	for (std::pair<std::string, int> name : countNames) {
		struct Line *newLine = new struct Line(
			{
				"    + " + name.first + ((name.second == 1) ? "" : " x" + std::to_string(name.second)),
				descriptionPanel.defaultColor
			}
		);

		inventoryPanel.text.push_back(newLine);
	}
}


/*
	Change la couleur de la ligne se situant aux coordonnees [x, y]
*/
void InfoPanel::HighlightLineAtCoords(int x, int y)
{
	int countLines = 0;
	int linePadding = 0;
	std::string::iterator itrLine;

	for (Panel *panel : panels) {
		countLines++; //Pour le header
		countLines += panel->origY; //Pour le padding entre chaque panel
		
		/* Si la ligne selectionnee se situe dans le panel parcouru alors on compte jusqu'a trouver la bonne ligne*/
		if (y <= countLines + panel->text.size()) {
			for (Line *line : panel->text) {

				/* Compte le nombre d'espaces se situant à l'avant de la ligne */
				itrLine = line->text.begin();
				linePadding = 0;
				while (itrLine != line->text.end() && *(itrLine++) == ' ') linePadding++;

				if (y == countLines && x >= linePadding && x < line->text.length()) {
					if (highlightedLine != line) {
						RemoveHighlight();
						/* On garde en memoire la ligne pour pouvoir retablir son ancienne couleur plus tard */
						highlightedLine = line;
						oldColorHighlightedLine = line->color;
						line->color = panel->defaultHighlight;
					}
					return;
				}
				
				countLines++;
			}
		}
	}

	RemoveHighlight();
}

/*
	Retablit l'ancienne couleur de la ligne mise en surbrillance
*/
void InfoPanel::RemoveHighlight() {
	if (highlightedLine != nullptr) highlightedLine->color = oldColorHighlightedLine;
	highlightedLine = nullptr;
}