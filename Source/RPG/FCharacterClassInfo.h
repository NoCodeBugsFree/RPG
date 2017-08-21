// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FCharacterClassInfo.generated.h"

USTRUCT(BlueprintType)
struct FCharacterClassInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	/** The name of the class  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	FString Class_Name;

	/** Starting max HP  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	int32 StartMHP;

	/**  Starting max MP */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	int32 StartMMP;

	/** Starting attack  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	int32 StartATK;

	/** Starting defense  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	int32 StartDEF;

	/** Starting luck  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	int32 StartLuck;

	/** Max HP at level 50  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	int32 EndMHP;

	/** Max MP at level 50  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	int32 EndMMP;

	/** Attack at level 50  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	int32 EndATK;

	/** Defense at level 50  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	int32 EndDEF;

	/** Luck at level 50  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	int32 EndLuck;

	/** Starting abilities  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	TArray<FString> StartingAbilities;

	/** Learned abilities  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	TArray<FString> LearnedAbilities;

	/** Learned ability levels  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ClassInfo")
	TArray<int32> LearnedAbilityLevels;

};

USTRUCT(BlueprintType)
struct FCharacterInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	/** Character's name  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterInfo")
	FString Character_Name;

	/** Class identification  */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterInfo")
	FString Class_ID;

};

USTRUCT(BlueprintType)
struct FEnemyInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** Enemy Name  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyInfo")
	FString EnemyName;

	/** Mana  */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EnemyInfo")
	int32 MHP;
	
	/** Attack  */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EnemyInfo")
	int32 ATK;

	/** defense   */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EnemyInfo")
	int32 DEF;

	/** Luck */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EnemyInfo")
	int32 Luck;

	/** Abilities */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EnemyInfo")
	TArray<FString> Abilities;

	/** Reward gold amount  */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "EnemyInfo")
	int32 Gold;

};

USTRUCT(BlueprintType)
struct FItemsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ItemData")
	int32 HP;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ItemData")
	int32 MP;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ItemData")
	int32 ATK;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ItemData")
	int32 DEF;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ItemData")
	int32 Luck;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ItemData")
	int32 Gold;
};