#pragma once

#ifndef DEF_TREEOBJECT
#define DEF_TREEOBJECT

#define TREE_HEALTH 4

#include "BreakableObject.h"

class TreeObject :	public BreakableObject {

public:
	TreeObject(int x, int y, std::string spriteFile);
	TreeObject(int x, int y, std::string spriteFile, std::string mapName);
	~TreeObject();

	inline std::string GetDescription() const override { return "a huge tree"; }

	void OnClick() override;
	void OnBreak() override;
};

#endif