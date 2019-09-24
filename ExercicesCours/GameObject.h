#pragma once
class GameObject {

	int posX;
	int posY;


	int spriteWidth;
	int spriteHeight;
	char* sprite;

public:
	GameObject(int x, int y);
	~GameObject();

	void Init();
	void Update();
};

