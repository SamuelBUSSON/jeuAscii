#pragma once

#ifndef DEF_MONSTEROBJECT
#define DEF_MONSTEROBJECT

#include "BreakableObject.h"


#include "MonsterStates.h"
#include "StateMachine.h"

#define MONSTER_HEALTH 5
#define MONSTER_RANGE_DETECTION 20

class MonsterObject : public BreakableObject
{

private:
	StateMachine<MonsterObject>*  stateMachine;

public:
	MonsterObject(int x, int y, std::string spriteFile);
	MonsterObject(int x, int y, std::string spriteFile, std::string mapName);
	~MonsterObject();

	StateMachine<MonsterObject>* GetFSM()const { return stateMachine; }

	void UpdateDescription() override;

	void OnClick() override;
	void OnBreak() override;

	void Update();

	int GetCenterX();
	int GetCenterY();

	bool IsInRange(int x, int y);
	
};

#endif