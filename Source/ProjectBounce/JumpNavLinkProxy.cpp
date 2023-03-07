// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpNavLinkProxy.h"
#include "GameFramework/Character.h"

FVector AJumpNavLinkProxy::CalculateVelocity(FVector EndLocation, FVector StartLocation, float Duration)
{
    float InDuration = Duration;

    float XDifference = EndLocation.X - StartLocation.X;
    float YDifference = EndLocation.Y - StartLocation.Y;

    float ZDifference = pow(InDuration, 2);
    ZDifference *= -0.5f;
    ZDifference *= 982.0f;
    ZDifference += StartLocation.Z;
    ZDifference -= EndLocation.Z;
    

    XDifference = XDifference / InDuration;
    YDifference = YDifference / InDuration;
    ZDifference = ZDifference / InDuration;
    
    
    return FVector(XDifference, YDifference, ZDifference * -1.0f);
}


/*
void AJumpNavLinkProxy::ReceiveSmartLinkReached(AActor* Agent, const FVector& Destination)
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Jump"));
}

*/

