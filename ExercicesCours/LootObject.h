#pragma once
#include "GameObject.h"
class LootObject : public GameObject
{
public:
	LootObject(int x, int y, std::string spriteFile, std::string mapLink);
	~LootObject();
	void OnClick() override;
	virtual void OnUse() = 0;
	virtual std::string GetName() const = 0;
};

