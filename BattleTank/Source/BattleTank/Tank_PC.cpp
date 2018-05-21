// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank_PC.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

void ATank_PC::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

}

void ATank_PC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATank_PC::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {return;}
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
		DrawDebugPoint(
			GetWorld(),
			HitLocation,
			10,
			FColor(255,0,255),
			true,
			0.03
		);
	}
}

bool ATank_PC::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation,
		ViewportSizeY*CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
		return true;
	}	

	return false;
}

/************************************************************************/
/* 通过屏幕空间位置获取观察朝向                                              */
/************************************************************************/
bool ATank_PC::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

/**
通过朝向查找射击到的点
*/
bool ATank_PC::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
	
}

ATank* ATank_PC::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}