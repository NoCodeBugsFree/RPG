// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGGameInstance.h"
#include "GameCharacter.h"
#include "FCharacterClassInfo.h"

URPGGameInstance::URPGGameInstance()
{

}

void URPGGameInstance::Init()
{
	if (bIsInitialized)
	{
		return;
	}

	bIsInitialized = true;

	 
	// locate characters asset
	UDataTable* characters = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), 
		NULL, TEXT("DataTable'/Game/Misc/CharacterInfoDataTable.CharacterInfoDataTable'")));
	if (characters == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Characters data table not found!"));
		return;
	}

	// locate character
	FCharacterInfo* row = characters->FindRow<FCharacterInfo>(TEXT("S1"), TEXT("LookupCharacterClass"));
	if (row == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Character ID 'S1' not found!"));
		return;
	}
	
	// add character to party
	PartyMembers.Add(UGameCharacter::CreateGameCharacter(row, this));
	


	// -----------------------------------------------------------------------------------

	/** ME  */
	//if (CharactersInfoDataTable)
	//{
	//	FCharacterInfo* row = CharactersInfoDataTable->FindRow<FCharacterInfo>(TEXT("S1"), TEXT("MyLookupCharacterClass"));
	//	if (row == NULL)
	//	{
	//		UE_LOG(LogTemp, Error, TEXT("Character ID 'S1' not found!"));
	//		return;
	//	}
	//	// add character to party
	//	PartyMembers.Add(UGameCharacter::CreateGameCharacter(row, this));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("CharactersInfoDataTable == NULL"));
	//}
}

void URPGGameInstance::PrepareReset()
{
	bIsInitialized = false;
}
