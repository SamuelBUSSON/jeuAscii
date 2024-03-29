#pragma once

#ifndef DEF_STONEOBJECT
#define DEF_STONEOBJECT

#define STONE_HEALTH 8

#include "BreakableObject.h"

class StoneObject : public BreakableObject {

public:
	StoneObject(int x, int y, std::string spriteFile);
	StoneObject(int x, int y, std::string spriteFile, std::string mapName);
	~StoneObject();

	void UpdateDescription() override;
	void OnClick() override;
	void OnBreak() override;
};

#endif