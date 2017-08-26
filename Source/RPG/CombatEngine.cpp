// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatEngine.h"

CombatEngine::CombatEngine(TArray<UGameCharacter*> NewPlayerParty, TArray<UGameCharacter*> NewEnemyParty)
{
	PlayerParty = NewPlayerParty;
	EnemyParty = NewEnemyParty;

	// first add all players to combat order
	for (int i = 0; i < PlayerParty.Num(); i++)
	{
		CombatantOrder.Add(PlayerParty[i]);
	}

	// next add all enemies to combat order
	for (int i = 0; i < EnemyParty.Num(); i++)
	{
		CombatantOrder.Add(EnemyParty[i]);
	}

	for (int i = 0; i < CombatantOrder.Num(); i++)
	{
		CombatantOrder[i]->CombatInstance = this;
	}

	TickTargetIndex = 0;

	SetPhase(ECombatPhase::CPhase_Decision);
}

CombatEngine::~CombatEngine()
{
	// free enemies
	for (int i = 0; i < EnemyParty.Num(); i++)
	{
		EnemyParty[i] = nullptr;
	}
	for (int i = 0; i < CombatantOrder.Num(); i++)
	{
		CombatantOrder[i]->CombatInstance = nullptr;
	}
}

bool CombatEngine::Tick(float DeltaSeconds)
{
	switch(CombatPhase)
	{
		// ---------  Decision  ----------------------
		case ECombatPhase::CPhase_Decision:
		{
			if (!bWaitingForCharacter)
			{
				CurrentTickTarget->BeginMakeDecision();
				bWaitingForCharacter = true;
			}
			bool bDecisionMade = CurrentTickTarget->MakeDecision(DeltaSeconds);
			if (bDecisionMade)
			{
				SelectNextCharacter();
				// no next character, switch to action phase
				if (TickTargetIndex == -1)
				{
					SetPhase(ECombatPhase::CPhase_Action);
				}
			}
		}
		break;
		
		// ---------  Action  ------------------------
		case ECombatPhase::CPhase_Action:

		{
			if (!bWaitingForCharacter)
			{
				CurrentTickTarget->BeginExecuteAction();
				bWaitingForCharacter = true;
			}
			bool bActionFinished = CurrentTickTarget->ExecuteAction(DeltaSeconds);
			if (bActionFinished)
			{
				SelectNextCharacter();
				// no next character, switch to action ??? phase (m.b. decision???)
				if (TickTargetIndex == -1)
				{
					SetPhase(ECombatPhase::CPhase_Decision);
				}
			}
		}
		break;
		// in case of victory or combat, return true (combat is finished)

		// ---------  GameOver and Victory  ----------------
		case ECombatPhase::CPhase_GameOver:
		case ECombatPhase::CPhase_Victory:
			return true;
			break;
	}

	// check for game over
	int DeadCount = 0;
	for (int i = 0; i < PlayerParty.Num(); i++)
	{
		if (PlayerParty[i]->HP <= 0)
		{
			DeadCount++;
		}
	}

	// all players have died, switch to game over phase
	if (DeadCount == PlayerParty.Num())
	{
		SetPhase(ECombatPhase::CPhase_GameOver);
		return false;
	}

	// check for victory
	DeadCount = 0;
	int32 Gold = 0;
	int32 XP = 0;
	for (int i = 0; i < EnemyParty.Num(); i++)
	{
		if (EnemyParty[i]->HP <= 0)
		{
			DeadCount++;
			Gold += EnemyParty[i]->Gold;
			XP = EnemyParty[i]->XP;
		}
	}

	// all enemies have died, switch to victory phase
	if (DeadCount == EnemyParty.Num())
	{
		SetPhase(ECombatPhase::CPhase_Victory);
		GoldTotal = Gold;
		XPTotal = XP;
		return false;
	}

	// if execution reaches here, combat has not finished - return false
	return false;
}

void CombatEngine::SetPhase(ECombatPhase NewCombatPhase)
{
	CombatPhase = NewCombatPhase;

	switch (CombatPhase)
	{
		// ---------  Action  ------------------------
		case ECombatPhase::CPhase_Action:

		// ---------  Decision  ----------------------
		case ECombatPhase::CPhase_Decision:

			// set the active target to the first character in the combat order
			TickTargetIndex = 0;

			SelectNextCharacter();

			break;

		// ---------  Victory  ------------------------
		case ECombatPhase::CPhase_Victory:

			// todo: handle victory

			break;

		// ---------  GameOver  ------------------------
		case ECombatPhase::CPhase_GameOver:

			// todo: handle game over

			break;
	}
}

void CombatEngine::SelectNextCharacter()
{
	bWaitingForCharacter = false;

	for (int32 i = TickTargetIndex; i < CombatantOrder.Num(); i++)
	{
		UGameCharacter* GameCharacter = CombatantOrder[i];
		if (GameCharacter->HP > 0)
		{
			TickTargetIndex = i + 1;
			CurrentTickTarget = GameCharacter;
			return;
		}
	}
	TickTargetIndex = -1;
	CurrentTickTarget = nullptr;
}
