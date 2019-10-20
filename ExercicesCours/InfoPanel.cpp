#include "pch.h"
#include "InfoPanel.h"
#include "ItemInfoLine.h"
#include "GameManager.h"


#include <map>
#include <iostream>


InfoPanel::InfoPanel()
{
	descriptionPanel.marginX = 0;
	descriptionPanel.marginY = 0;
	descriptionPanel.header = new InfoLine("Description :", 0x07);
	descriptionPanel.text.push_back(new InfoLine("", descriptionPanel.defaultColor));
	panels.push_back(&descriptionPanel);

	inventoryPanel.marginX = 0;
	inventoryPanel.marginY = 8;
	inventoryPanel.header = new InfoLine("Inventory :", 0x07);
	inventoryPanel.padding = 4;
	panels.push_back(&inventoryPanel);

	craftPanel.marginX = 0;
	craftPanel.marginY = 18;
	craftPanel.header = new InfoLine("Craft :", 0x07);
	craftPanel.padding = 4;
	panels.push_back(&craftPanel);

	highlightedLine = nullptr;
	oldColorHighlightedLine = 0;

	healthBar.origX = 0;
	healthBar.origY = GAME_SCREEN_HEIGHT - 5;
	healthBar.label = new InfoLine("Health :", 0x07);
	healthBar.color = 0xc0;
	healthBar.value = GameManager::Instance().GetPlayer()->GetHealth();
	healthBar.maxValue = GameManager::Instance().GetPlayer()->GetMaxHealth();

	foodBar.origX = 0;
	foodBar.origY = healthBar.origY + 2;
	foodBar.label = new InfoLine("Food :", 0x07);
	foodBar.color = 0x20;
	foodBar.value = GameManager::Instance().GetPlayer()->GetFood();
	foodBar.maxValue = GameManager::Instance().GetPlayer()->GetMaxFood();
}


InfoPanel::~InfoPanel()
{
	for (Panel* panel : panels)
	{
		delete panel->header;
		panel->clear();
	}
}


void InfoPanel::SetDescription(std::string str)
{ 
	descriptionPanel.clear();

	int strSize = str.size();
	int strBeginCut = 0;
	int strCutSize = GAME_SCREEN_WIDTH - (descriptionPanel.padding + descriptionPanel.marginX + INFO_PANEL_ORIG_X + 1);
	std::string hyphen = "";
	do {
		if (str.size() > strCutSize &&
			strSize > strCutSize &&
			str.substr(strBeginCut + strCutSize - 1, 1).compare(" ") != 0)
		{
			if (str.substr(strBeginCut + strCutSize - 2, 1).compare(" ") == 0) {
				hyphen = " ";
			}
			else {
				hyphen = "-";
			}
		}

		descriptionPanel.text.push_back(
			new InfoLine(
				str.substr(strBeginCut, strCutSize - hyphen.size()) + hyphen,
				descriptionPanel.defaultColor
			)
		);
		strSize -= strCutSize - hyphen.size();
		strBeginCut += strCutSize - hyphen.size();
		hyphen = "";
	} while (strSize > 0);
}


void InfoPanel::SetInventory(std::list<Item *> inventory) {
	inventoryPanel.clear();

	/* Pour ne pas avoir de doublons dans l'inventaire */
	std::map<std::string, std::list<Item*>> countItems;
	for (Item *item : inventory) {
		countItems[item->GetName()].push_back(item);
	}

	for (std::pair<std::string, std::list<Item*>> item : countItems) {
		ItemInfoLine *newItemLine = new ItemInfoLine(
			"+ " + item.first + ((item.second.size() == 1) ? "" : " x" + std::to_string(item.second.size())),
			descriptionPanel.defaultColor,
			item.second
		);

		inventoryPanel.text.push_back(newItemLine);
	}
}


void InfoPanel::SetCrafts(std::list<CraftableItem *> items)
{
	craftPanel.clear();

	for (CraftableItem *item : items) {
		craftPanel.text.push_back(new ItemInfoLine(
			"+ " + item->GetName(),
			(GameManager::Instance().CanCraft(item) ? 0x0a : craftPanel.defaultColor),
			item
		));
	}
}

/*
	Retourne la ligne de texte se situant aux coordonnees [x, y]
*/
InfoLine *InfoPanel::FindLineAtCoords(int x, int y)
{
	size_t countLines = 0;

	for (Panel *panel : panels) {
		/* Si la ligne selectionnee se situe dans le panel parcouru alors on compte jusqu'a trouver la bonne ligne */
		if (y <= panel->marginY + panel->text.size()) {
			countLines = panel->marginY + 1; //Pour le margin entre chaque panel et le header
			for (InfoLine *line : panel->text) {
				if (y == countLines && x >= panel->padding && x < panel->padding + line->text.length()) {
					return line;
				}
				countLines++;
			}
		}
	}

	return nullptr;
}

/*
	Change la couleur de la ligne se situant aux coordonnees [x, y]
*/
void InfoPanel::HighlightLineAtCoords(int x, int y)
{
	InfoLine *line = FindLineAtCoords(x, y);
	if (line != nullptr) {
		if (highlightedLine != line) {
			RemoveHighlight();
			/* On garde en memoire la ligne pour pouvoir retablir son ancienne couleur plus tard */
			highlightedLine = line;
			oldColorHighlightedLine = line->color;
			line->color = defaultHighlight;
			line->OnHighlight();
		}
		return;
	}

	RemoveHighlight();
}

/*
	Retablit l'ancienne couleur de la ligne mise en surbrillance
*/
void InfoPanel::RemoveHighlight() {
	if (highlightedLine != nullptr) {
		highlightedLine->color = oldColorHighlightedLine;
		highlightedLine->OnLeaveHighlight();
	}

	highlightedLine = nullptr;
}


/*
	Declenche le OnClick de la ligne situee aux coordonnees [x, y]
*/
void InfoPanel::ClickOnCoords(int x, int y)
{
	InfoLine *line = FindLineAtCoords(x, y);

	if (line != nullptr) {
		line->OnClick();
	}
}