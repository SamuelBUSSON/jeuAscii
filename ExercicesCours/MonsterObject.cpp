#include "pch.h"
#include "MonsterObject.h"


MonsterObject::MonsterObject(int x, int y, std::string spriteFile)
	: BreakableObject(x, y, spriteFile, MONSTER_HEALTH), brain_timer(BRAIN_FRAMERATE){
	description = "A Monster !!";

	//set up state machine
	stateMachine = new StateMachine<MonsterObject>(this);
	brain_timer.Start();

	stateMachine->SetCurrentState(SeekPlayer::Instance());
}

MonsterObject::MonsterObject(int x, int y, std::string spriteFile, std::string mapName)
	: BreakableObject(x, y, spriteFile, MONSTER_HEALTH, mapName), brain_timer(BRAIN_FRAMERATE) {
	description = "A Monster !!";

	//set up state machine
	stateMachine = new StateMachine<MonsterObject>(this);

	brain_timer.Start();
	stateMachine->SetCurrentState(SeekPlayer::Instance());



}


MonsterObject::~MonsterObject()
{
}

void MonsterObject::UpdateDescription()
{

}

void MonsterObject::OnClick()
{

}

void MonsterObject::OnBreak()
{

}

void MonsterObject::Update()
{
	if (brain_timer.ReadyForNextFrame()) 
	{
		stateMachine->Update();
	}
}

int MonsterObject::GetCenterX()
{
	return posX + sprite.width/2;
}

int MonsterObject::GetCenterY()
{
	return posY + sprite.height / 2;
}

bool MonsterObject::IsInRange(int x, int y)
{
	if ( (x > GetCenterX() - MONSTER_RANGE_DETECTION && x < GetCenterX() + MONSTER_RANGE_DETECTION) && (y < GetCenterY() + MONSTER_RANGE_DETECTION/2 && y > GetCenterY() - MONSTER_RANGE_DETECTION/2)) {
		return true;
	}
	return false;
}
