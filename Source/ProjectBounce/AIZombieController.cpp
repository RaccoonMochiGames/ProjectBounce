// Fill out your copyright notice in the Description page of Project Settings.


#include "AIZombieController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ZombieCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


AAIZombieController::AAIZombieController(const FObjectInitializer & ObjectInitializer)
{
    BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard Component"));
    BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
}

void AAIZombieController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    AZombieCharacter* Chr = Cast<AZombieCharacter>(InPawn);
    if(Chr != nullptr && Chr->TreeAsset != nullptr)
    {
        // Initialize Blackboard
        BBC->InitializeBlackboard(*Chr->TreeAsset->BlackboardAsset);

        // Setup Blackboard key
        ZombieKeyId = BBC->GetKeyID("TargetActor");

        // Start Behavior Tree
        BTC->StartTree(*Chr->TreeAsset);
    }
}



