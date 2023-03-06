// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolLocation.h"
#include "AIController.h"
#include "ZombieCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"

UBTTask_FindPatrolLocation::UBTTask_FindPatrolLocation(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bCreateNodeInstance = true;
    NodeName = "Find Patrol Location";
}

EBTNodeResult::Type UBTTask_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
    AAIController* MyController = OwnerComp.GetAIOwner();

    if(!MyController || !MyBlackboard)
        return EBTNodeResult::Failed;

    AZombieCharacter* Chr = Cast<AZombieCharacter>(MyController->GetPawn());
    if(!Chr)
        return EBTNodeResult::Failed;


    FVector Result;
    if(GetRandomPointInRadius(Chr->GetActorLocation(), 300000, Result))
    {
        OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>("PatrolLocation", Result);
        return EBTNodeResult::Succeeded;
    }

    
    return EBTNodeResult::Failed;

}

bool UBTTask_FindPatrolLocation::GetRandomPointInRadius(const FVector& Origin, float Radius, FVector& OutResult)
{	
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys)
	{
		return false;
	}
	
	FVector Result;
	bool bSuccess = NavSys->K2_GetRandomReachablePointInRadius(GetWorld(), Origin, Result, Radius);

	//Out
	OutResult = Result;
	return bSuccess;
}