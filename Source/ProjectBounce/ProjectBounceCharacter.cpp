// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectBounceCharacter.h"
#include "ProjectBounceProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"


//////////////////////////////////////////////////////////////////////////
// AProjectBounceCharacter

AProjectBounceCharacter::AProjectBounceCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create the hitbox for hitting tennis balls
	ProjectileHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileHitBox"));
	ProjectileHitBox->SetupAttachment(FirstPersonCameraComponent);
	ProjectileHitBox->SetRelativeLocation(FVector(110.0f, 0.0f, -4.0f));

	// Projectile not in range
	bProjectileInRange = false;
}

void AProjectBounceCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// declare overlap events
	ProjectileHitBox->OnComponentBeginOverlap.AddDynamic(this, &AProjectBounceCharacter::OnOverlapBegin); 
	ProjectileHitBox->OnComponentEndOverlap.AddDynamic(this, &AProjectBounceCharacter::OnOverlapEnd); 

	// declare any necessary variables
	iAmmoCount = 1;
}

//////////////////////////////////////////////////////////////////////////// Input

void AProjectBounceCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event and hit event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AProjectBounceCharacter::OnPrimaryAction);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Pressed, this, &AProjectBounceCharacter::OnSecondaryAction);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AProjectBounceCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AProjectBounceCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AProjectBounceCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AProjectBounceCharacter::LookUpAtRate);
}

void AProjectBounceCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(OtherActor->IsA(AProjectBounceProjectile::StaticClass()))
	{
		bProjectileInRange = true;
		GEngine->AddOnScreenDebugMessage(4, 15.0f, FColor::Green, TEXT("Tennis ball has come in range!"));

		AProjectile = Cast<AProjectBounceProjectile>(OtherActor);
						
		if(Cast<AProjectBounceProjectile>(OtherActor)->bJustSpawned)
		{
			Cast<AProjectBounceProjectile>(OtherActor)->bJustSpawned = false;
		}
		else
		{
			OtherActor->CustomTimeDilation = 0.5f;
		}
	}
}

void AProjectBounceCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->IsA(AProjectBounceProjectile::StaticClass()))
	{
		bProjectileInRange = false;
		GEngine->AddOnScreenDebugMessage(4, 15.0f, FColor::Green, TEXT("Tennis ball has left range!"));

		//OtherActor->CustomTimeDilation = 1.0f;
		AimedAtBall = OtherActor;

		ReturnBallSpeed(AimedAtBall);

		AProjectile = NULL;
	}
}

void AProjectBounceCharacter::OnPrimaryAction()
{
	if(iAmmoCount > 0)
	{
		iAmmoCount--;

		// Trigger the OnItemUsed Event
		OnUseItem.Broadcast();
	}
	else
	{
			// Get the nearest tennis ball and add velocity
		if(bProjectileInRange == true)
		{
			GEngine->AddOnScreenDebugMessage(4, 15.0f, FColor::Green, TEXT("Hitting Tennis ball!!!"));

			if(AProjectile != NULL)
			{
				FVector forwardVector = FirstPersonCameraComponent->GetForwardVector();

				AProjectile->BallHit(forwardVector);

				ReturnBallSpeed(AimedAtBall);

				if(FireAnimation != nullptr)
				{
					// Get the animation object for the arms mesh
					UAnimInstance* AnimInstance = GetMesh1P()->GetAnimInstance();
					if (AnimInstance != nullptr)
					{
						AnimInstance->Montage_Play(FireAnimation, 1.f);
					}
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(4, 15.0f, FColor::Green, TEXT("No Tennis ball in range..."));
		}
	}
}

void AProjectBounceCharacter::OnSecondaryAction()
{

}

void AProjectBounceCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnPrimaryAction();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AProjectBounceCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void AProjectBounceCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AProjectBounceCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AProjectBounceCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AProjectBounceCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

bool AProjectBounceCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AProjectBounceCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AProjectBounceCharacter::EndTouch);

		return true;
	}
	
	return false;
}

void AProjectBounceCharacter::GainAmmo()
{
	iAmmoCount++;

	// Tell weapon
}

void AProjectBounceCharacter::ReturnBallSpeed(AActor* Ball)
{
	Ball->CustomTimeDilation = 1.0f;
}


