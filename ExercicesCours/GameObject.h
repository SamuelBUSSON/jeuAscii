#pragma once

#ifndef DEF_GAMEOBJECT
#define DEF_GAMEOBJECT

#include <string>

struct Sprite {
	std::string spriteFile;
	int width;
	int height;
};

class GameObject {

private:
	struct Sprite sprite;

protected:
	int posX;
	int posY;

public:
	GameObject(int x, int y, std::string spriteFile);
	~GameObject();

	void Init();
	virtual void OnClick();

	bool SpriteIsOnCoords(int x, int y);


	inline int GetX() const { return posX; }
	inline int GetY() const { return posY; }
};

#endif