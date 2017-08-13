// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RPGCameraComponent.h"

// Sets default values
ARPGCharacter::ARPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 540.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	RPGCameraComponent = CreateDefaultSubobject<URPGCameraComponent>(TEXT("RPGCameraComponent"));
	RPGCameraComponent->SetupAttachment(RootComponent);
	RPGCameraComponent->CameraPitch = -50.f;
	RPGCameraComponent->CameraDistance = 600.f;

}

void ARPGCharacter::MoveVertical(float Value)
{
	if (Controller != NULL && Value != 0.0f)
	{
		const FVector MovementDirection = FVector(1, 0, 0);
		AddMovementInput(MovementDirection, Value);
	}
}

void ARPGCharacter::MoveHorizontal(float Value)
{
	if (Controller != NULL && Value != 0.0f)
	{
		const FVector MovementDirection = FVector(0, 1, 0);
		AddMovementInput(MovementDirection, Value);
	}
}

// Called when the game starts or when spawned
void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

