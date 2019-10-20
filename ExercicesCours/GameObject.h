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

protected:
	struct Sprite sprite;
	int posX;
	int posY;

	int colliderStartX;
	int colliderStartY;
	int colliderEndX;
	int colliderEndY;

	int shakeCounter;

	std::string map_link;

	std::string description;

public:
	GameObject(int x, int y, std::string spriteFile);
	GameObject(int x, int y, std::string spriteFile, std::string mapName);
	~GameObject();

	void Init();
	virtual void OnClick();

	bool SpriteIsOnCoords(int x, int y);
	bool SpriteIsOnCoordsAndMap(int x, int y, std::string map_name);
	bool SpriteColliderIsOnCoordsAndMap(int x, int y, std::string map_name);
	Sprite LoadSpriteFile(std::string spriteFile);

	void DrawCollider();

	void SetSpriteFile(std::string c);

	inline int GetX() const { return posX; }
	inline int GetY() const { return posY; }
	inline int GetHeight() const { return sprite.height; }
	inline std::string GetMapLink() const { return map_link; }

	inline std::string GetDescription() const { return description; }

	inline std::string GetSpriteFileName() const { return sprite.spriteFile; }


	inline void IncreaseShake() { shakeCounter++; }

	void SetX(int x);
	void SetY(int y);

	inline void SetMapLink(std::string mapName) { map_link = mapName; }
};

#endif