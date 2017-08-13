// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatAction.h"

class TestCombatAction : public ICombatAction
{

public:

	TestCombatAction();

	TestCombatAction(UGameCharacter* NewTarget);

	virtual void BeginExecuteAction(UGameCharacter* NewCharacter) override;

	virtual bool ExecuteAction(float DeltaSeconds) override;

protected:

	UGameCharacter* Character;

	UGameCharacter* Target;

	float DelayTimer;

};