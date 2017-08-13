// Fill out your copyright notice in the Description page of Project Settings.

#include "TestDecisionMaker.h"
#include "TestCombatAction.h"

// Add default functionality here for any ITestDecisionMaker functions that are not pure virtual.

void TestDecisionMaker::BeginMakeDecision(UGameCharacter* Character)
{
	// pick a target
	UGameCharacter* Target = Character->SelectTarget();
	Character->CombatAction = new TestCombatAction(Target);
}

bool TestDecisionMaker::MakeDecision(float DeltaSeconds)
{
	return true;
}
