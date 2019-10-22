#pragma once
#include "State.h"

class MonsterObject;

class SeekPlayer : public State<MonsterObject>
{
private:

	SeekPlayer() {}

	//copy ctor and assignment should be private
	SeekPlayer(const SeekPlayer&);
	SeekPlayer& operator=(const SeekPlayer&);

public:

	//this is a singleton
	static SeekPlayer* Instance();

	virtual void Enter(MonsterObject* monster);

	virtual void Execute(MonsterObject* monster);

	virtual void Exit(MonsterObject* monster);


};

class ChasePlayer : public State<MonsterObject>
{
private:

	ChasePlayer() {}

	//copy ctor and assignment should be private
	ChasePlayer(const ChasePlayer&);
	ChasePlayer& operator=(const ChasePlayer&);

public:

	//this is a singleton
	static ChasePlayer* Instance();

	virtual void Enter(MonsterObject* monster);

	virtual void Execute(MonsterObject* monster);

	virtual void Exit(MonsterObject* monster);


};

class FightPlayer : public State<MonsterObject>
{
private:

	int spriteValue = 0;
	int spriteChange = 8;

	FightPlayer() {}

	//copy ctor and assignment should be private
	FightPlayer(const FightPlayer&);
	FightPlayer& operator=(const FightPlayer&);

public:

	//this is a singleton
	static FightPlayer* Instance();

	virtual void Enter(MonsterObject* monster);

	virtual void Execute(MonsterObject* monster);

	virtual void Exit(MonsterObject* monster);


};

