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
	InfoLine *emptyLine = new InfoLine("", descriptionPanel.defaultColor);
	descriptionPanel.text.push_back(emptyLine);
	panels.push_back(&descriptionPanel);

	inventoryPanel.marginX = 0;
	inventoryPanel.marginY = 3;
	inventoryPanel.header = new InfoLine("Inventory :", 0x07);
	inventoryPanel.padding = 4;
	panels.push_back(&inventoryPanel);

	highlightedLine = nullptr;
	oldColorHighlightedLine = 0;

	healthBar.origX = 0;
	healthBar.origY = SCREEN_HEIGHT - 5;
	healthBar.label = new InfoLine("Health :", 0x07);
	healthBar.color = 0xc0;
	healthBar.value = GameManager::instance().GetPlayer()->GetHealth();
	healthBar.maxValue = GameManager::instance().GetPlayer()->GetMaxHealth();

	foodBar.origX = 0;
	foodBar.origY = healthBar.origY + 2;
	foodBar.label = new InfoLine("Food :", 0x07);
	foodBar.color = 0x20;
	foodBar.value = GameManager::instance().GetPlayer()->GetFood();
	foodBar.maxValue = GameManager::instance().GetPlayer()->GetMaxFood();
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

	InfoLine *newLine = new InfoLine(str, descriptionPanel.defaultColor);
	descriptionPanel.text.push_front(newLine);
}


void InfoPanel::SetInventory(std::list<LootObject *> inventory) {
	inventoryPanel.clear();

	/* Pour ne pas avoir de doublons dans l'inventaire */
	std::map<std::string, std::list<LootObject*>> countLoot;
	for (LootObject *loot : inventory) {
		countLoot[loot->GetName()].push_back(loot);
	}

	for (std::pair<std::string, std::list<LootObject*>> loot : countLoot) {
		ItemInfoLine *newItemLine = new ItemInfoLine(
			"+ " + loot.first + ((loot.second.size() == 1) ? "" : " x" + std::to_string(loot.second.size())),
			descriptionPanel.defaultColor,
			loot.second
		);

		inventoryPanel.text.push_back(newItemLine);
	}
	


	/*for (LootObject* lootObject : inventory) {
		ItemInfoLine *newItemLine = new ItemInfoLine(
			"+ " + lootObject->GetName(),
			descriptionPanel.defaultColor,
			lootObject
		);

		inventoryPanel.text.push_back(newItemLine);
	}*/
}

/*
	Retourne la ligne de texte se situant aux coordonnees [x, y]
*/
InfoLine *InfoPanel::FindLineAtCoords(int x, int y)
{
	int countLines = 0;

	for (Panel *panel : panels) {
		countLines++; //Pour le header
		countLines += panel->marginY; //Pour le padding entre chaque panel

		/* Si la ligne selectionnee se situe dans le panel parcouru alors on compte jusqu'a trouver la bonne ligne*/
		if (y <= countLines + panel->text.size()) {
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