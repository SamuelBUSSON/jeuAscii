#pragma once

#ifndef DEF_GAMEOBJECT
#define DEF_GAMEOBJECT

#include <string>

struct Sprite {
	std::string spriteFile;
	int width;
	int height;
	int color;
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
	Sprite LoadSpriteFile(std::string spriteFile);


	inline int GetX() const { return posX; }
	inline int GetY() const { return posY; }
	inline int GetHeight() const { return sprite.height; }
	inline int GetColor() const { return sprite.color; }
	inline std::string GetSpriteFileName() const { return sprite.spriteFile; }

	inline void SetColor(int _color) { sprite.color = _color; }
};

#endif