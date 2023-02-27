// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectBounceProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AProjectBounceProjectile::AProjectBounceProjectile() 
{
	// Stop projectile from destroying
	InitialLifeSpan = 0.0f;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectBounceProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	PrimaryActorTick.bCanEverTick = true;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Custom projectile bounce variables
	maxBounces = 2;

	bRestState = false;
}

void AProjectBounceProjectile::BeginPlay()
{
	AActor::BeginPlay();

	currentBounces = maxBounces;
}

void AProjectBounceProjectile::Tick(float DeltaSeconds)
{


}

void AProjectBounceProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}

	// only reduce bounces if it is hitting a flat surface
	if(Hit.Normal == FVector(0.0f, 0.0f, 1.0f))
	{
		GEngine->AddOnScreenDebugMessage(3, 15.0f, FColor::Red, FString::Printf(TEXT("Hit flat surface! Bounces left: x: %d"), currentBounces));
		currentBounces--;
	}

	if(currentBounces <= 0 && bRestState == false)
	{		
		EnterRestState();
	}

	// Deletes a ball after being in rest state for a while
	if(currentBounces <= -5)
	{		
		Destroy();
	}

	if(bRestState)
	{
		// make it bounce in place
		ProjectileMovement->Velocity = FVector(0.0f, 0.0f, 600.0f);
	}

}

void AProjectBounceProjectile::EnterRestState()
{
	bRestState = true;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Entering rest state..."));

	// stop the projectiles velocity
	ProjectileMovement->SetVelocityInLocalSpace(FVector(0.0f, 0.0f, 0.0f));

}