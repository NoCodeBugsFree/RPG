// Fill out your copyright notice in the Description page of Project Settings.

#include "TestCombatAction.h"

TestCombatAction::TestCombatAction(UGameCharacter* NewTarget)
{
	Target = NewTarget;
}

TestCombatAction::TestCombatAction()
{

}

void TestCombatAction::BeginExecuteAction(UGameCharacter* NewCharacter)
{
	Character = NewCharacter;

	// no target, just return
	if (Target == nullptr)
	{
		return;
	}

	// target is dead, select another target
	if (Target->HP <= 0)
	{
		Target = Character->SelectTarget();
	}
	
	UE_LOG(LogTemp, Log, TEXT("%s attacks %s"), *Character->CharacterName, *Target->CharacterName);
	Target->HP -= (Character->ATK - Target->DEF) >= 0 ? Character->ATK - Target->DEF : 0;
	DelayTimer = 1.0f;
}

bool TestCombatAction::ExecuteAction(float DeltaSeconds)
{
	DelayTimer -= DeltaSeconds;
	return DelayTimer <= 0.0f;
}
