#pragma once

#ifndef DEF_CLICKABLEOBJECT
#define DEF_CLICKABLEOBJECT

#include "GameObject.h"
class ClickableObject :	public GameObject {
public:
	ClickableObject(int x, int y);
	~ClickableObject();

	void OnClick();
};

#endif