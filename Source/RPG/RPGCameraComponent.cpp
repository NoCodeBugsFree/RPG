// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGCameraComponent.h"


void URPGCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
	Super::GetCameraView(DeltaTime, DesiredView);

	DesiredView.Rotation = FRotator(CameraPitch, 0.0f, 0.0f);

	if ( APawn* OwningPawn = Cast<APawn>( GetOwner() ) )
	{
		FVector Location = OwningPawn->GetActorLocation();
		Location -= DesiredView.Rotation.Vector() * CameraDistance;
		DesiredView.Location = Location;
	}

}
