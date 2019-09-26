#include "pch.h"
#include "InfoPanel.h"

#include <map>


InfoPanel::InfoPanel()
{
	descriptionPanel.origX = 0;
	descriptionPanel.origY = 0;
	descriptionPanel.defaultColor = 0x08;
	descriptionPanel.header.color = 0x07;
	descriptionPanel.header.text = "Description :";
	panels.push_back(&descriptionPanel);

	inventoryPanel.origX = 0;
	inventoryPanel.origY = 3;
	inventoryPanel.defaultColor = 0x08;
	descriptionPanel.header.color = 0x07;
	inventoryPanel.header.text = "Inventory :";
	panels.push_back(&inventoryPanel);
}


InfoPanel::~InfoPanel()
{
}


void InfoPanel::SetInventory(std::list<LootObject *> inventory) {
	inventoryPanel.text.clear();
	std::map<std::string, int> countNames;
	for (LootObject *loot : inventory) {
		countNames[loot->GetName()]++;
	}

	for (std::pair<std::string, int> name : countNames) {
		inventoryPanel.textpush_back("    + " + name.first + ((name.second == 1) ? "" : " x" + std::to_string(name.second)));
	}
}

void InfoPanel::HighlightLineAtCoords(int x, int y) {

}