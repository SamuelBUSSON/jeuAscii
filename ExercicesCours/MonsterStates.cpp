#include "pch.h"
#include "MonsterStates.h"

#include "GameManager.h"
#include "State.h"
#include "MonsterObject.h"

SeekPlayer * SeekPlayer::Instance()
{

	static SeekPlayer instance;

	return &instance;
}

void SeekPlayer::Enter(MonsterObject * monster)
{
	monster->SetSpriteFile("Sprite/Monster.txt");

}

void SeekPlayer::Execute(MonsterObject * monster)
{
	GameObject* p = GameManager::Instance().GetPlayer();

	if (monster->IsInRange(p->GetX(), p->GetY()))
	{
		monster->GetFSM()->ChangeState(ChasePlayer::Instance());
	}



}

void SeekPlayer::Exit(MonsterObject * monster)
{

}

FightPlayer * FightPlayer::Instance()
{
	static FightPlayer instance;

	return &instance;
}

void FightPlayer::Enter(MonsterObject * monster)
{
}

void FightPlayer::Execute(MonsterObject * monster)
{
}

void FightPlayer::Exit(MonsterObject * monster)
{
}

ChasePlayer * ChasePlayer::Instance()
{
	static ChasePlayer instance;

	return &instance;
}

void ChasePlayer::Enter(MonsterObject * monster)
{
	monster->SetSpriteFile("Sprite/MonsterChase.txt");
}

void ChasePlayer::Execute(MonsterObject * monster)
{

	GameObject* p = GameManager::Instance().GetPlayer();

	if (!monster->IsInRange(p->GetX(), p->GetY()))
	{
		monster->GetFSM()->ChangeState(SeekPlayer::Instance());
	}
}

void ChasePlayer::Exit(MonsterObject * monster)
{
}
