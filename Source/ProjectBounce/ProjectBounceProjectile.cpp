// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectBounceProjectile.h"
#include "ProjectBounceCharacter.h"
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
	rallyCount = 0;

	bRestState = false;
}

void AProjectBounceProjectile::BeginPlay()
{
	AActor::BeginPlay();

	remainingBounces = maxBounces;
}

void AProjectBounceProjectile::Tick(float DeltaSeconds)
{
	// Update function
}

void AProjectBounceProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}

	if(OtherActor->IsA(AProjectBounceCharacter::StaticClass()) && !bRestState)
	{
		// when ball hits player, make it slow down a lot and go back into rest state
		ProjectileMovement->Velocity = (GetVelocity() * 0.3f);
		remainingBounces = 0;
	}

	if(OtherActor->IsA(AProjectBounceProjectile::StaticClass()))
	{
		// when ball hits ball, make it hit like a player hit it
		FVector direction = GetActorForwardVector();

		Cast<AProjectBounceProjectile>(OtherActor)->BallHit(direction);
	}

	// only reduce bounces if it is hitting a flat surface
	if(Hit.Normal == FVector(0.0f, 0.0f, 1.0f))
	{
		GEngine->AddOnScreenDebugMessage(3, 15.0f, FColor::Red, FString::Printf(TEXT("Hit flat surface! Bounces left: %d"), remainingBounces));
		remainingBounces--;

		if(remainingBounces <= 0 && bRestState == false)
		{		
			EnterRestState();
		}

	}
	else if(remainingBounces < maxBounces)
	{
		// Make it go towards player or enemy?
	}

	// Deletes a ball after being in rest state for a while
	if(remainingBounces <= -5)
	{		
		Destroy();
	}

	if(bRestState)
	{
		// make it bounce in place
		ProjectileMovement->Velocity = FVector(0.0f, 0.0f, 600.0f);

		if(OtherActor->IsA(AProjectBounceCharacter::StaticClass()))
		{
			Destroy();
		}
	}

}

void AProjectBounceProjectile::EnterRestState()
{
	bRestState = true;
	rallyCount = 0;

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Entering rest state..."));

	// stop the projectiles velocity
	ProjectileMovement->Velocity = FVector(0.0f, 0.0f, 0.0f);

}

void AProjectBounceProjectile::BallHit(FVector direction)
{
	float velocity = 0.1f;

	bRestState = false;
	//remainingBounces = maxBounces;

	GEngine->AddOnScreenDebugMessage(2, 2.0f, FColor::Blue, TEXT("Player has hit the ball!"));

	velocity = Rally(velocity);

	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Blue, FString::Printf(TEXT("Rally %d: %d"), rallyCount, remainingBounces));

	// Give the projectile a new direction and speed
	ProjectileMovement->Velocity = (direction * velocity);
}

float AProjectBounceProjectile::Rally(float velocity)
{
	rallyCount++;
	switch(rallyCount)
	{
		case 0:
			velocity = 2000.0f;
			remainingBounces = maxBounces;
			return velocity;
			break;
		case 1:
			velocity = 2200.0f;
			remainingBounces = maxBounces;
			return velocity;
			break;
		case 2:
			velocity = 2500.0f;
			remainingBounces = maxBounces + 1;
			return velocity;
			break;
		case 3:
			velocity = 3000.0f;
			remainingBounces = maxBounces + 1;
			return velocity;
			break;
		case 4:
			velocity = 3500.0f;
			remainingBounces = maxBounces + 2;
			return velocity;
			break;
		default:
			velocity = 3500.0f;
			remainingBounces = maxBounces + 2;
			return velocity;
			break;
	}
}