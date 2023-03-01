// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"


void AZombieAIController::BeginPlay()
{
    Super::BeginPlay();

    if(GetPawn() != nullptr)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("YES"));
    }
    const FVector DestinationLocation = FVector(1000.f, 0.f, 0.f); // Set the destination location
    MoveToLocation(DestinationLocation, 10.0f); // Move the character to the destination location with a speed of 10 units per second

}
/*
void AZombieAIController::MoveToLocation(const FVector& TargetLocation)
{
    APawn* ControlledPawn = GetPawn();

    if(ControlledPawn == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Could not find attached AI Pawn"));
        return;
    }

    UCharacterMovementComponent* CharacterMovement = ControlledPawn->FindComponentByClass<UCharacterMovementComponent>();

    if(CharacterMovement == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Could not find attached Character Movement Component"));
        return;
    }

    MoveToLocation(TargetLocation, 1000.0f);
}

*/

/*
void AZombieAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    if(Result.IsSuccess())
    {
        UE_LOG(LogTemp, Warning, TEXT("Movement Succeeded"));
    }
    else if (Result.IsInterrupted())
    {
        UE_LOG(LogTemp, Warning, TEXT("Move interrupted"));
    }
    else if (Result.IsFailure())
    {
        UE_LOG(LogTemp, Warning, TEXT("Move failed"));
    }
}
*/