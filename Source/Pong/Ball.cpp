// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set default components
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("BallMesh");
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");

	BallMesh->OnComponentHit.AddDynamic(this, &ABall::OnComponentHit);

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	// Rotate on start
	FRotator rotation = FRotator(Pitch, 46.0f, Roll);
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
		RotateOnHit(OtherActor);

		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
		if (GEngine)
		{
			FString msg = GetActorRotation().ToString();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%s"), *msg));
		}

		// Move Ball to prevent hitting twice
		FVector direction = GetActorForwardVector();
		AddMovementInput(direction, speed * FApp::GetDeltaTime());
	}
	
}

void ABall::RotateOnHit(AActor* OtherActor)
{
	float YawRotation, YawActor;
	YawActor = GetActorRotation().Yaw;


	
	if (OtherActor->IsA(AWalls::StaticClass()))
	{
		if ((YawActor > 0.0f && YawActor < 90.0f) ||
			(YawActor > -180.0f && YawActor < -90.0f))
		{
			YawRotation = 90.0f;
		}
		else
		{
			YawRotation = -90.0f;
		}
	}

	/*if (OtherActorName.Contains(PlayerName))
	{
		if ((YawActor > 0.0f && YawActor < 90.0f) ||
			(YawActor > -180.0f && YawActor < -90.0f))
		{
			YawRotation = -90.0f;
		}
		else
		{
			YawRotation = 90.0f;
		}
	}*/

	FRotator rotation = FRotator(Pitch, YawRotation, Roll);
	FQuat fQuat = FQuat(rotation);
	AddActorLocalRotation(fQuat);
}

