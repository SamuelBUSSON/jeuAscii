#pragma once

#ifndef DEF_GAMEOBJECT
#define DEF_GAMEOBJECT


struct Hitbox {
	int originX, originY, width, height;
};

class GameObject {

private:
	int spriteWidth;
	int spriteHeight;

	struct Hitbox hitbox;
	char* sprite;

protected:
	int posX;
	int posY;

public:
	GameObject(int x, int y);
	~GameObject();

	void Init();
	virtual void OnClick();

	bool HitboxIsOnCoords(int x, int y);


	inline int GetX() const { return posX; }
	inline int GetY() const { return posY; }
};

#endif