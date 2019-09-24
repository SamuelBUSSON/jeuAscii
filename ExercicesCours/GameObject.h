#pragma once

#ifndef DEF_GAMEOBJECT
#define DEF_GAMEOBJECT

class GameObject {

private:
	int spriteWidth;
	int spriteHeight;
	char* sprite;

protected:
	int posX;
	int posY;

public:
	GameObject(int x, int y);
	~GameObject();

	void Init();
	virtual void OnClick();

	inline const int GetX() const { return posX; }
	inline const int GetY() const { return posY; }
};

#endif