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

	// Random rotate on start
	RandomRotate();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (hasHit) hitTimer += DeltaTime;

	if (hitTimer >= maxHitTimer)
	{
		hasHit = false;
		hitTimer = 0.0f;
	}

	if (isMoving)
	{
		AddMovementInput(movingDirection, speed * DeltaTime);
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
		if (!hasHit)
		{
			RotateOnHit(OtherActor);
			hasHit = true;
		}

		// Move Ball to prevent hitting twice
		/*FVector direction = GetActorForwardVector();
		AddMovementInput(direction, speed * FApp::GetDeltaTime());*/
	}
	
}

void ABall::RotateOnHit(AActor* OtherActor)
{
	float ResYaw, ActorYaw;
	ActorYaw = GetActorRotation().Yaw;


	
	if (OtherActor->IsA(AWalls::StaticClass()))
	{
		ChangeDirectionOnWallHit();
	}

	if (OtherActor->IsA(AMyPlayer::StaticClass()))
	{
		if ((ActorYaw > 0.0f && ActorYaw < 90.0f) ||
			(ActorYaw > -180.0f && ActorYaw < -90.0f))
		{
			ResYaw = -CalcRotAngleOnPlayerHit(OtherActor);
		}
		else
		{
			ResYaw = CalcRotAngleOnPlayerHit(OtherActor);
		}
	}


	
}

void ABall::RandomRotate()
{
	//float rotateValue = FMath::FRandRange(-180.0f, 180.0f);
	float rotateValue = 50.0f;
	FRotator rotator = FRotator(Pitch, rotateValue, Roll);
	movingDirection = rotator.RotateVector(GetActorForwardVector());
}

void ABall::ChangeDirectionOnWallHit()
{
	// Reverse the X value
	movingDirection = FVector(-movingDirection.X, movingDirection.Y, movingDirection.Z);

	if (DebugPrint)
	{
		PrintOnScreen(movingDirection.ToString());
	}	
}



float ABall::CalcRotAngleOnPlayerHit(AActor * OtherActor)
{
	FVector ActorVector, ResVector;
	ActorVector = GetActorForwardVector();

	// Reverse the Y value
	ResVector = FVector(ActorVector.X, -ActorVector.Y, ActorVector.Z);

	return CalcAngleBetweenVectors(ActorVector, ResVector);
}

float ABall::CalcAngleBetweenVectors(FVector Vector1, FVector Vector2)
{	
	return FMath::RadiansToDegrees(acosf(FVector::DotProduct(Vector1, Vector2)));
}

void ABall::PrintOnScreen(FString message)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%s"), *message));
	}
}



