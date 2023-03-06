// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayer.h"
#include "AIController.h"
#include "ZombieCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTTask_FindPlayer::UBTTask_FindPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bCreateNodeInstance = true;
    NodeName = "Find Player";
}

EBTNodeResult::Type UBTTask_FindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
    AAIController* MyController = OwnerComp.GetAIOwner();

    if(!MyController || !MyBlackboard)
        return EBTNodeResult::Failed;

    AZombieCharacter* Chr = Cast<AZombieCharacter>(MyController->GetPawn());
    if(!Chr)
        return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>("TargetActor",  UGameplayStatics::GetPlayerCharacter(this, 0));

    return EBTNodeResult::Succeeded;
}