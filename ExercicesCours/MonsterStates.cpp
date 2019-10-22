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
	monster->SetSpriteFile("Sprite/MonsterAttack1.txt");

}

void FightPlayer::Execute(MonsterObject * monster)
{
	Player* p = GameManager::Instance().GetPlayer();

	if (!monster->IsNear(p->GetX(), p->GetY()))
	{
		monster->GetFSM()->ChangeState(ChasePlayer::Instance());
	}

	if (spriteValue % spriteChange == 1)
	{
		p->GetDammage(monster->GetDamageValue());
		spriteValue = 1;
	}

	spriteValue++;

	monster->SetSpriteFile(spriteValue % spriteChange == 0 ? "Sprite/MonsterAttack2.txt"  : "Sprite/MonsterAttack1.txt");
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

	if (p->GetX() != monster->GetCenterX()) 
	{		
		p->GetX() > monster->GetCenterX() ? monster->MoveEast() : monster->MoveWest();
	}
	else {
		if (p->GetY() != monster->GetCenterY())
		{
			p->GetY() > monster->GetCenterY() ? monster->MoveSouth() : monster->MoveNorth();
		}
	}


	if (!monster->IsInRange(p->GetX(), p->GetY()))
	{
		monster->GetFSM()->ChangeState(SeekPlayer::Instance());
	}
	
	if (monster->IsNear(p->GetX(), p->GetY()))
	{
		monster->GetFSM()->ChangeState(FightPlayer::Instance());
	}
}

void ChasePlayer::Exit(MonsterObject * monster)
{
}
