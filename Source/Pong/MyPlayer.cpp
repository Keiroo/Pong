// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayer.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlayerMesh");
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
	
	if (MeshMaterial != NULL)
	{
		PlayerMesh->SetMaterial(0, MeshMaterial);
	}
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyPlayer::MovePlayer(float AxisValue)
{
	if (AxisValue > 0.0f)
	{
		PlayerInput = 1.0f * PlayerSpeed;
	}
	else if (AxisValue < 0.0f)
	{
		PlayerInput = -1.0f * PlayerSpeed;
	}
	else return;

	FVector MoveVector = FVector(PlayerInput, 0.0f, 0.0f);	
	AddMovementInput(MoveVector);
}

