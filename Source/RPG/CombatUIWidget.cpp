// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatUIWidget.h"
#include "TestCombatAction.h"
#include "CombatEngine.h"

void UCombatUIWidget::BeginMakeDecision(UGameCharacter* Target)
{
	CurrentTarget = Target;
	bIsDecisionFinished = false;
	ShowActionsPanel(Target);
}

bool UCombatUIWidget::MakeDecision(float DeltaSeconds)
{
	return bIsDecisionFinished;
}

TArray<UGameCharacter*> UCombatUIWidget::GetCharacterTargets()
{
	if (CurrentTarget)
	{
		if (CurrentTarget->bIsPlayer)
		{
			return CurrentTarget->CombatInstance->EnemyParty;
		}
		else
		{
			return CurrentTarget->CombatInstance->PlayerParty;
		}
	}
	else
	{
		TArray<UGameCharacter*> EmptyArray;
		return EmptyArray;
	}
}

void UCombatUIWidget::AttackTarget(UGameCharacter* Target)
{
	TestCombatAction* Action = new TestCombatAction(Target);
	CurrentTarget->CombatAction = Action;
	bIsDecisionFinished = true;
}
