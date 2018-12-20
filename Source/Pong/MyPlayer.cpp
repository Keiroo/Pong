#include "MyPlayer.h"

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlayerMesh");
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
	
	if (MeshMaterial != NULL)
	{
		PlayerMesh->SetMaterial(0, MeshMaterial);
	}
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

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

