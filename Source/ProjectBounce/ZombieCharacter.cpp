// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieCharacter.h"
#include "Components/CapsuleComponent.h"
// Sets default values
AZombieCharacter::AZombieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;




	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));


	MeshComponent->SetStaticMesh(Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"))));

	MeshComponent->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
	


	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("Actor location: %s"), *PlayerLocation.ToString());
	Cast<AAIController>(GetController())->MoveToActor(PlayerCharacter);

	

}

// Called every frame
void AZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// Called to bind functionality to input
void AZombieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

