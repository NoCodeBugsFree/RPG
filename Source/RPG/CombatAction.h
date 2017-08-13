// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameCharacter.h"

class UGameCharacter;

class ICombatAction
{

public:

	/** takes a pointer to the character that this action is executing for.  */
	virtual void BeginExecuteAction(UGameCharacter* character) = 0;

	/** takes the duration of the previous frame in seconds */
	virtual bool ExecuteAction(float DeltaSeconds) = 0;

};
