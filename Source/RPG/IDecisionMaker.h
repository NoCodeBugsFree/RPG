// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameCharacter.h"

class UGameCharacter;

class IDecisionMaker
{

public:

	virtual void BeginMakeDecision(UGameCharacter* Character) = 0;

	virtual bool MakeDecision(float DeltaSeconds) = 0;

};
