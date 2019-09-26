#include "pch.h"
#include "InfoPanel.h"


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
