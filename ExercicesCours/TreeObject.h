#pragma once

#ifndef DEF_TREEOBJECT
#define DEF_TREEOBJECT

#define TREE_HEALTH 4

#include "BreakableObject.h"

class TreeObject :	public BreakableObject {

public:
	TreeObject(int x, int y);
	~TreeObject();

	void OnClick() override;
	void OnBreak() override;
};

#endif