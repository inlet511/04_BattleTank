// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	
	auto ControlledPawn = Cast<ATank>(GetPawn());
	auto PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (ControlledPawn)
	{
		ControlledPawn->AimAt(PlayerPawn->GetActorLocation());

		ControlledPawn->Fire();
	}
}