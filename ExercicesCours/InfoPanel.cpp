#include "pch.h"
#include "InfoPanel.h"

#include <map>


InfoPanel::InfoPanel()
{
	descriptionPanel.origX = 0;
	descriptionPanel.origY = 0;
	descriptionPanel.color = 0x08;
	descriptionPanel.headerColor = 0x07;
	descriptionPanel.text.push_front("");
	descriptionPanel.header = "Description :";
	panels.push_back(&descriptionPanel);

	inventoryPanel.origX = 0;
	inventoryPanel.origY = 3;
	inventoryPanel.color = 0x08;
	descriptionPanel.headerColor = 0x07;
	inventoryPanel.header = "Inventory :";
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
		inventoryPanel.text.push_back("    + " + name.first + ((name.second == 1) ? "" : " x" + std::to_string(name.second)));
	}
}