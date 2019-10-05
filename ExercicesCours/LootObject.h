#pragma once
#include "GameObject.h"
class LootObject : public GameObject
{
protected:
	std::string name;
public:
	LootObject(int x, int y, std::string spriteFile, std::string mapLink);
	~LootObject();
	void OnClick() override;
	virtual void OnUse() = 0;
	const std::string GetName() const { return name; }
};

