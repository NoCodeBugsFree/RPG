// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPG.h"
#include "GameCharacter.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECombatPhase : uint8
{
	CPhase_Decision  UMETA(DisplayName = "Decision"),
	CPhase_Action    UMETA(DisplayName = "Action"),
	CPhase_Victory   UMETA(DisplayName = "Victory"),
	CPhase_GameOver  UMETA(DisplayName = "GameOver"),
};

class RPG_API CombatEngine
{

public:

	CombatEngine(TArray<UGameCharacter*> NewPlayerParty,TArray<UGameCharacter*> NewEnemyParty);

	~CombatEngine();

	UPROPERTY()
	TArray<UGameCharacter*> CombatantOrder;

	UPROPERTY()
	TArray<UGameCharacter*> PlayerParty;

	UPROPERTY()
	TArray<UGameCharacter*> EnemyParty;
	
	ECombatPhase CombatPhase;

	/** will be responsible for holding the total amount of XP gained from battle if
	  * all of the enemies have perished  
	  */
	int32 XPTotal;

	int32 GoldTotal;

	/** This will be used to switch between, for example, BeginMakeDecision and MakeDecision .  */
	bool bWaitingForCharacter;

	/**   
	*	The CombatEngine class defines a Tick method. This will be called by the game mode of
	*	very frame as long as combat is not over, and it returns true when combat has finished
	*	(or false otherwise).
	*/
	bool Tick(float DeltaSeconds);
	
	void SetPhase(ECombatPhase NewCombatPhase);

protected:

	/** During the Decision and Action phases,
	*	we�ll keep a pointer to a single character.   
	*/
	UPROPERTY()
	UGameCharacter* CurrentTickTarget;

	int32 TickTargetIndex;

	void SelectNextCharacter();

};
