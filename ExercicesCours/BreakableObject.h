#pragma once

#ifndef DEF_BREAKABLEOBJECT
#define DEF_BREAKABLEOBJECT

#include "GameObject.h"
class BreakableObject :	public GameObject {
private:
	int health;

public:
	BreakableObject(int x, int y, int health);
	~BreakableObject();

	virtual void OnClick() override;
	virtual void OnBreak() = 0;
};

#endif