// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create default components
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

	// Timer to prevent multiple rotations
	if (hasHit) hitTimer += DeltaTime;
	if (hitTimer >= maxHitTimer)
	{
		hasHit = false;
		hitTimer = 0.0f;
	}

	if (isMoving)
	{
		AddMovementInput(movingDirection, BallSpeed * DeltaTime);
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
	}	
}

void ABall::RotateOnHit(AActor* OtherActor)
{
	if (OtherActor->IsA(AWalls::StaticClass()))
	{
		ChangeDirectionOnWallHit();
	}

	if (OtherActor->IsA(AMyPlayer::StaticClass()))
	{
		ChangeDirectionOnPlayerHit(OtherActor);
	}	
}

void ABall::RandomRotate()
{
	float rotateValue = FMath::FRandRange(-180.0f, 180.0f);
	FRotator rotator = FRotator(0.0f, rotateValue, 0.0f);
	movingDirection = rotator.RotateVector(GetActorForwardVector());
}

void ABall::ChangeDirectionOnWallHit()
{
	// Reverse the X value
	movingDirection = FVector(-movingDirection.X, movingDirection.Y, movingDirection.Z);

	if (DebugPrint) PrintOnScreen(movingDirection.ToString());
}

void ABall::ChangeDirectionOnPlayerHit(AActor * OtherActor)
{
	// Get player's mesh size and origin
	FVector Origin, BoxExtent;
	OtherActor->GetActorBounds(true, Origin, BoxExtent);

	// Get X values of Origin and BoxExtent
	float OriginX = Origin.X;
	float BoxExtentX = BoxExtent.X;

	// Get Ball location
	float BallPosX = GetActorLocation().X;

	if ((BallPosX < OriginX + BoxExtentX) &&
		(BallPosX > OriginX - BoxExtentX))
	{
		//Calc hit point
		float hitPoint = -(OriginX - BallPosX);
		float hitPointNormalized = hitPoint / BoxExtentX;
		float bounceAngle = hitPointNormalized * MaxBounceAngle;

		FVector vector;
		FRotator rotator;

		if (movingDirection.Y > 0.0f)
		{
			vector = FVector(0.0f, -1.0f, 0.0f);
			rotator = FRotator(0.0f, bounceAngle, 0.0f);
		}
		else
		{
			vector = FVector(0.0f, 1.0f, 0.0f);
			rotator = FRotator(0.0f, -bounceAngle, 0.0f);
		}

		
		movingDirection = rotator.RotateVector(vector);

		if (DebugPrint) PrintOnScreen(movingDirection.ToString());
	}
	// If not, use same logic as walls
	else
	{
		ChangeDirectionOnWallHit();
	}
}

void ABall::PrintOnScreen(FString message)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%s"), *message));
	}
}



