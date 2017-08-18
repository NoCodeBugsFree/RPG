// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RPGGameInstance.generated.h"

/**
 * 
 */
class UGameCharacter;

UCLASS()
class RPG_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	URPGGameInstance();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	class UDataTable* CharactersInfoDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Data")
	TArray<UGameCharacter*> PartyMembers;

	void Init();

	/** In this case, the purpose of PrepareReset is to set isInitialized to false so that the
		next time Init is called, the party members are cleared and reloaded (we don’t want to
		reset the game with dead party members!).  
	*/
	void PrepareReset();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Data")
	bool TalkShop;

protected:

	bool bIsInitialized;
	
private:
	
	
};
