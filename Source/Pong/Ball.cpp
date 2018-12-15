// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set default components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");

	StaticMesh->OnComponentHit.AddDynamic(this, &ABall::OnComponentHit);

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	Yaw = 45.0f;
	FRotator rotation = FRotator(Pitch, Yaw, Roll);

	FQuat fQuat = FQuat(rotation);

	AddActorLocalRotation(fQuat);
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{
		FVector direction = GetActorForwardVector();
		AddMovementInput(direction, speed * DeltaTime);
	}
}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABall::OnComponentHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		FString BPWallsName = "BP_Walls";
		if (OtherActor->GetName().Contains(BPWallsName))
		{
			isMoving = false;
		}

		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
	}
	
}

