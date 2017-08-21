// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FCharacterClassInfo.h"
#include "GameCharacter.generated.h"

/**
 * 
 */
class CombatEngine;
class ICombatAction;
class IDecisionMaker;

UCLASS(BlueprintType)
class RPG_API UGameCharacter : public UObject
{
	GENERATED_BODY()
	
public:

	CombatEngine* CombatInstance;
	
	FCharacterClassInfo* ClassInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
	int32 MHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
	int32 MMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
	int32 MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
	int32 ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
	int32 DEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterInfo)
	int32 LUCK;

	/** Current Gold amount  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = CharacterInfo)
	int32 Gold;

	// -----------------------------------------------------------------------------------

	static UGameCharacter* CreateGameCharacter(FCharacterInfo* characterInfo, UObject* outer);

	static UGameCharacter* CreateGameCharacter(FEnemyInfo* enemyInfo, UObject* outer);
	
	void BeginDestroy() override;

	void BeginMakeDecision();

	bool MakeDecision(float DeltaSeconds);

	void BeginExecuteAction();

	bool ExecuteAction(float DeltaSeconds);

	UGameCharacter* SelectTarget();
	
	bool bIsPlayer;

public:

	ICombatAction* CombatAction;

	IDecisionMaker* DecisionMaker;

};
