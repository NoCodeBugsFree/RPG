// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameCharacter.h"
#include "IDecisionMaker.h"
#include "CombatUIWidget.generated.h"

/**
 * 
 */

UCLASS()
class RPG_API UCombatUIWidget : public UUserWidget, public IDecisionMaker
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
	void AddPlayerCharacterPanel(UGameCharacter* Target);

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
	void AddEnemyCharacterPanel(UGameCharacter* Target);

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
	void ShowActionsPanel(UGameCharacter* Target);

	virtual void BeginMakeDecision(UGameCharacter* Target) override;

	virtual bool MakeDecision(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Combat UI")
	TArray<UGameCharacter*> GetCharacterTargets();

	UFUNCTION(BlueprintCallable, Category = "Combat UI")
	void AttackTarget(UGameCharacter* Target);

protected:

	UGameCharacter* CurrentTarget;

	/** This will be used to signal that a decision has been made (and that MakeDecision should return true ).  */
	bool bIsDecisionFinished;
		
};
