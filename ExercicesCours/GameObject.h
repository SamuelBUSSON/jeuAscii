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
	void Update();
};

#endif