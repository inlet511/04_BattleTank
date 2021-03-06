// Fill out your copyright notice in the Description page of Project Settings.
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto TankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s Intend move forward throw:%f"), *TankName, Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend TurnRight throw:%f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
}
