// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayer.h"
#include "AIController.h"
#include "ZombieCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
UBTTask_FindPlayer::UBTTask_FindPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bCreateNodeInstance = true;
    NodeName = "Find Player";
}

EBTNodeResult::Type UBTTask_FindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
    AAIController* MyController = OwnerComp.GetAIOwner();
    bool test = MyController->LineOfSightTo(UGameplayStatics::GetPlayerCharacter(this, 0));
    if(!MyController || !MyBlackboard)
        return EBTNodeResult::Failed;

    AZombieCharacter* Chr = Cast<AZombieCharacter>(MyController->GetPawn());
    if(!Chr)
        return EBTNodeResult::Failed;



    if(test)
    {
        OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>("TargetActor",  UGameplayStatics::GetPlayerCharacter(this, 0));
          OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>("HasLineofSight", test);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;

}