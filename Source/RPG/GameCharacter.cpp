// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCharacter.h"
#include "CombatEngine.h"
#include "TestCombatAction.h"
#include "CombatAction.h"
#include "IDecisionMaker.h"
#include "TestDecisionMaker.h"

/**
	This factory method takes a pointer
	to an FCharacterInfo struct, which is returned from a Data Table, and also an Outer
	object, which is passed to the NewObject function. It then attempts to find the character
	class Data Table from a path, and if the result is not null, it locates the proper row in the
	Data Table, stores the result, and also initializes the stats and the CharacterName field.
 */
UGameCharacter* UGameCharacter::CreateGameCharacter(FCharacterInfo* characterInfo, UObject* outer)
{
	UGameCharacter* character = NewObject<UGameCharacter>(outer);
	
	// locate character classes asset
	UDataTable* characterClasses = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(),
		NULL, TEXT("DataTable'/Game/Misc/CharactersDataTable.CharactersDataTable'")));

	if (characterClasses == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Character classes datatable not found!"));
	}
	else
	{
		character->CharacterName = characterInfo->Character_Name;
		FCharacterClassInfo* row = characterClasses->FindRow<FCharacterClassInfo>(*(characterInfo->Class_ID), TEXT("LookupCharacterClass"));
		character->ClassInfo = row;
		character->MHP = character->ClassInfo->StartMHP;
		character->MMP = character->ClassInfo->StartMMP;
		character->HP = character->MHP;
		character->MP = character->MMP;
		character->ATK = character->ClassInfo->StartATK;
		character->DEF = character->ClassInfo->StartDEF;
		character->LUCK = character->ClassInfo->StartLuck;
		
		character->bIsPlayer = true;
	}
	
	return character;
}

UGameCharacter* UGameCharacter::CreateGameCharacter(FEnemyInfo* enemyInfo, UObject* outer)
{
	UGameCharacter* character = NewObject<UGameCharacter>(outer);
	character->CharacterName = enemyInfo->EnemyName;
	character->ClassInfo = nullptr;
	character->MHP = enemyInfo->MHP;
	character->MMP = 0;
	character->HP = enemyInfo->MHP;
	character->MP = 0;
	character->ATK = enemyInfo->ATK;
	character->DEF = enemyInfo->DEF;
	character->LUCK = enemyInfo->Luck;
	character->Gold = enemyInfo->Gold;
	
	character->DecisionMaker = new TestDecisionMaker();
	character->bIsPlayer = false;

	return character;
}

void UGameCharacter::BeginDestroy()
{
	Super::BeginDestroy();

	if (!bIsPlayer)
	{
		delete(DecisionMaker);
	}
}

void UGameCharacter::BeginMakeDecision()
{
	DecisionMaker->BeginMakeDecision(this);
}

bool UGameCharacter::MakeDecision(float DeltaSeconds)
{
	return DecisionMaker->MakeDecision(DeltaSeconds);
}

void UGameCharacter::BeginExecuteAction()
{
	CombatAction->BeginExecuteAction(this);
}

bool UGameCharacter::ExecuteAction(float DeltaSeconds)
{
	bool bFinishedAction = CombatAction->ExecuteAction(DeltaSeconds);
	if (bFinishedAction)
	{
		delete(CombatAction);
		return true;
	}
	return false;
}

UGameCharacter* UGameCharacter::SelectTarget()
{
	UGameCharacter* Target = nullptr;

	TArray<UGameCharacter*> TargetList = CombatInstance->EnemyParty;
	if (!bIsPlayer)
	{
		TargetList = CombatInstance->PlayerParty;
	}
	for (int i = 0; i < TargetList.Num(); i++)
	{
		if (TargetList[i]->HP > 0)
		{
			Target = TargetList[i];
			break;
		}
	}
	if (Target->HP <= 0)
	{
		return nullptr;
	}
	return Target;
}
