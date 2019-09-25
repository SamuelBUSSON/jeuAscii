#pragma once

#ifndef DEF_BREAKABLEOBJECT
#define DEF_BREAKABLEOBJECT

#include "GameObject.h"
#include <string>

class BreakableObject :	public GameObject {
private:
	int health;

public:
	BreakableObject(int x, int y, std::string spriteFile, int health);
	BreakableObject(int x, int y, std::string spriteFile, int _health, std::string mapName);
	~BreakableObject();

	virtual std::string GetDescription() const = 0;

	virtual void OnClick() override;
	virtual void OnBreak() = 0;
};

#endif