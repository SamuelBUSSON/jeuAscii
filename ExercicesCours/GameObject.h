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

protected:
	struct Sprite sprite;
	int posX;
	int posY;
	std::string map_link;

public:
	GameObject(int x, int y, std::string spriteFile);
	GameObject(int x, int y, std::string spriteFile, std::string mapName);
	~GameObject();

	void Init();
	virtual void OnClick();

	bool SpriteIsOnCoords(int x, int y);
	bool SpriteIsOnCoordsAndMap(int x, int y, std::string map_name);
	Sprite LoadSpriteFile(std::string spriteFile);


	inline int GetX() const { return posX; }
	inline int GetY() const { return posY; }
	inline int GetHeight() const { return sprite.height; }
	inline int GetColor() const { return sprite.color; }
	inline std::string GetMapLink() const { return map_link; }

	virtual std::string GetDescription() const = 0;

	inline std::string GetSpriteFileName() const { return sprite.spriteFile; }

	inline void SetColor(int _color) { sprite.color = _color; }
	inline void SetX(int x) { posX = x; }
	inline void SetY(int y) { posY = y; }
	inline void SetMapLink(std::string mapName) { map_link = mapName; }
};

#endif