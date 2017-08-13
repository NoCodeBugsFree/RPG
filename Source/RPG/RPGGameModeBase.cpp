// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGGameModeBase.h"
#include "RPGCharacter.h"
#include "RPGPlayerController.h"
#include "RPGGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "CombatUIWidget.h"

ARPGGameModeBase::ARPGGameModeBase()
{
	PlayerControllerClass = ARPGPlayerController::StaticClass();
	DefaultPawnClass = ARPGCharacter::StaticClass();
}

void ARPGGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Cast<URPGGameInstance>(GetGameInstance())->Init();
}

void ARPGGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CurrentCombatInstance)
	{
		bool bIsCombatOver = CurrentCombatInstance->Tick(DeltaSeconds);
		if (bIsCombatOver)
		{
			for (int32 i = 0; i < CurrentCombatInstance->PlayerParty.Num(); i++)
			{
				CurrentCombatInstance->PlayerParty[i]->DecisionMaker = nullptr;
			}


			if (CurrentCombatInstance->CombatPhase == ECombatPhase::CPhase_GameOver)
			{
				UE_LOG(LogTemp, Log, TEXT("Player loses combat, game over"));

				Cast<URPGGameInstance>(GetGameInstance())->PrepareReset();
				UUserWidget* GameOverUIInstance = CreateWidget<UUserWidget>(GetGameInstance(), GameOverUIClass);
				GameOverUIInstance->AddToViewport();
			}
			else if (CurrentCombatInstance->CombatPhase == ECombatPhase::CPhase_Victory)
			{
				UE_LOG(LogTemp, Log, TEXT("Player wins combat"));
			}
			
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetActorTickEnabled(true);
			delete(CurrentCombatInstance);
			CurrentCombatInstance = nullptr;
			EnemyParty.Empty();
			
			CombatUIInstance->RemoveFromViewport();
			CombatUIInstance = nullptr;
		}
	}
}

void ARPGGameModeBase::TestCombat()
{
	UDataTable* EnemyDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL,
		TEXT("DataTable'/Game/Misc/EnemiesDataTable.EnemiesDataTable'")));

	if (EnemyDataTable == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemies data table not found!"));
		return;
	}

	FEnemyInfo* row = EnemyDataTable->FindRow<FEnemyInfo>(TEXT("S1"), TEXT("LookupEnemyInfo"));
	if (row == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy ID 'S1' not found!"));
		return;
	}

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetActorTickEnabled(false);

	UGameCharacter* EnemyCharacter = UGameCharacter::CreateGameCharacter(row, this);
	EnemyParty.Add(EnemyCharacter);
	URPGGameInstance* RPGGameInstance = Cast<URPGGameInstance>(GetGameInstance());
	CurrentCombatInstance = new CombatEngine(RPGGameInstance->PartyMembers, EnemyParty);
	UE_LOG(LogTemp, Log, TEXT("Combat started"));
	
	CombatUIInstance = CreateWidget<UCombatUIWidget>(GetGameInstance(), CombatUIClass);

	CombatUIInstance->AddToViewport();

	for (int32 i = 0; i < RPGGameInstance->PartyMembers.Num(); i++)
	{
		CombatUIInstance->AddPlayerCharacterPanel(RPGGameInstance->PartyMembers[i]);
		RPGGameInstance->PartyMembers[i]->DecisionMaker = CombatUIInstance;
	}

	for (int32 i = 0; i < EnemyParty.Num(); i++)
	{
		CombatUIInstance->AddEnemyCharacterPanel(EnemyParty[i]);
	}
}

