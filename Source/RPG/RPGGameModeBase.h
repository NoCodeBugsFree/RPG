// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CombatEngine.h"
#include "RPGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API ARPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	ARPGGameModeBase();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	CombatEngine* CurrentCombatInstance;

	TArray<UGameCharacter*> EnemyParty;

	UFUNCTION(Exec, BlueprintCallable)
	void TestCombat();

protected:

	UPROPERTY()
	class UCombatUIWidget* CombatUIInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UCombatUIWidget> CombatUIClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> GameOverUIClass;

private:
	

};
