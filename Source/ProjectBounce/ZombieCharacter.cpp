// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ProjectBounceProjectile.h"
#include "Components/SceneComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

class UCharacterMovementComponent;
class USceneComponent;
// Sets default values
AZombieCharacter::AZombieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates Cube mesh and and attaches to Capsule component
	
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;



}

// Called when the game starts or when spawned
void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AZombieCharacter::OnHit);


	health = maxHealth;	
}

// Called every frame
void AZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isDead)
	{
		DeathTimer += DeltaTime;
		if(DeathTimer >= DeathDelay)
		{
			Destroy();
		}
	}

}

void AZombieCharacter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AProjectBounceProjectile* projectile = Cast<AProjectBounceProjectile>(OtherActor);
	if(projectile && health >= 50.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("LOL"));
		health -= 50.0f;
		GetCharacterMovement()->DoJump(false);
		LaunchCharacter(FVector(projectile->GetVelocity().X * 0.5f, projectile->GetVelocity().Y * 0.5f, 300), true, true);
		return; 
	}
	
	if(projectile)
	{
		GetCharacterMovement()->DoJump(false);
		LaunchCharacter(FVector(projectile->GetVelocity().X * 1.5f, projectile->GetVelocity().Y * 1.5f, 500), true, true);
		FindComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(true);

		isDead = true;
	}
	
	
}

// Called to bind functionality to input
void AZombieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

