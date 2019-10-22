#pragma once

#ifndef DEF_MONSTEROBJECT
#define DEF_MONSTEROBJECT

#include "BreakableObject.h"


#include "PrecisionTimer.h"
#include "MonsterStates.h"
#include "StateMachine.h"

#define MONSTER_HEALTH 5
#define MONSTER_RANGE_DETECTION 20
#define BRAIN_FRAMERATE 15

class MonsterObject : public BreakableObject
{

private:
	StateMachine<MonsterObject>*  stateMachine;	
	PrecisionTimer brain_timer;

	int atkDamage = 1;

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

	bool IsNear(int x, int y);

	bool CanMove(int x, int y);

	void MoveEast();
	void MoveWest();
	void MoveNorth();
	void MoveSouth();

	inline int GetDamageValue() { return atkDamage; }
	
};

#endif