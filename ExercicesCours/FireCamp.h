#pragma once

#ifndef DEF_FIRECAMP
#define DEF_FIRECAMP

#include "GameObject.h"

class FireCamp : public GameObject {
public:
	FireCamp(int x, int y, std::string spriteFile);
	~FireCamp();

	inline std::string GetDescription() const override { return "a fire camp"; }
};

#endif
