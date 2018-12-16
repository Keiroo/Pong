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
	BallMesh->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	// Save actorZ value
	ActorZ = GetActorLocation().Z;

	// Random rotate on start
	RandomRotate();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{
		FVector direction = GetActorForwardVector();
		AddMovementInput(direction, Speed * DeltaTime);
	}

	// Prevent from moving in Z vector
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, ActorZ));
}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABall::OnComponentHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	FloatingPawnMovement->Velocity = FVector::ZeroVector;
	FloatingPawnMovement->UpdateComponentVelocity();

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		RotateOnHit(OtherActor);

		// DEBUG LOG
		if (DebugLog)
		{
			/*if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
			if (GEngine)
			{
				FString msg = GetActorRotation().ToString();
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Current rotation: %s"), *msg));
			}*/
		}

		// Move Ball to prevent hitting twice
		/*FVector direction = GetActorForwardVector();
		AddMovementInput(direction, Speed);*/
	}
	
}

void ABall::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FloatingPawnMovement->Velocity = FVector::ZeroVector;
	FloatingPawnMovement->UpdateComponentVelocity();

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		RotateOnHit(OtherActor);

		// DEBUG LOG
		/*if (DebugLog)
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
			if (GEngine)
			{
				FString msg = GetActorRotation().ToString();
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Current rotation: %s"), *msg));
			}
		}*/

		// Move Ball to prevent hitting twice
		/*FVector direction = GetActorForwardVector();
		AddMovementInput(direction, Speed);*/
	}


}

void ABall::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABall::RotateOnHit(AActor* OtherActor)
{
	float ResYaw, ActorYaw;
	FRotator rotation;
	ActorYaw = GetActorRotation().Yaw;


	
	if (OtherActor->IsA(AWalls::StaticClass()))
	{
		if ((ActorYaw > 0.0f && ActorYaw < 90.0f) ||
			(ActorYaw > -180.0f && ActorYaw < -90.0f))
		{
			ResYaw = CalcRotAngleOnWallHit();
		}
		else
		{
			ResYaw = -CalcRotAngleOnWallHit();
		}
		rotation = FRotator(Pitch, ResYaw, Roll);
	}

	if (OtherActor->IsA(AMyPlayer::StaticClass()))
	{
		/*if ((ActorYaw > 0.0f && ActorYaw < 90.0f) ||
			(ActorYaw > -180.0f && ActorYaw < -90.0f))
		{
			ResYaw = -CalcRotAngleOnPlayerHit(OtherActor);
		}
		else
		{
			ResYaw = CalcRotAngleOnPlayerHit(OtherActor);
		}*/

		FVector ResVector = CalcRotVectorOnPlayerHit(OtherActor);
		ResYaw = CalcAngleBetweenVectors(GetActorForwardVector(), ResVector);
		// Check rotation direction

		ResVector.Normalize();		
		if (GetActorForwardVector().X < ResVector.X)
		{
			ResYaw = -ResYaw;
		}
		
		
		
				
		//rotation = UKismetMathLibrary::FindLookAtRotation(GetActorForwardVector(), ResVector);
		
		rotation = FRotator(Pitch, ResYaw, Roll);

		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetActorForwardVector().ToString());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ResVector.ToString());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::SanitizeFloat(ResYaw));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *rotation.ToString());

		/*DebugMsg(GetActorForwardVector().ToString());
		DebugMsg(ResVector.ToString());
		DebugMsg(FString::SanitizeFloat(ResYaw));
		DebugMsg(rotation.ToString());*/

		// DEBUG LOG
		/*if (DebugLog)
		{
			if (GEngine)
			{
				FString msg = FString::SanitizeFloat(ResYaw);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Angle: %s"), *msg));
			}
		}*/
	}

	// Rotate ball
	
	FQuat fQuat = FQuat(rotation);
	AddActorLocalRotation(fQuat);
}

void ABall::RandomRotate()
{
	//float rotateValue = FMath::FRandRange(-180.0f, 180.0f);
	float rotateValue = 89.0f;
	FRotator rotation = FRotator(Pitch, rotateValue, Roll);
	FQuat fQuat = FQuat(rotation);
	AddActorLocalRotation(fQuat);
}

float ABall::CalcRotAngleOnWallHit()
{
	FVector ActorVector, ResVector;
	ActorVector = GetActorForwardVector();

	// Reverse the X value
	ResVector = FVector(-ActorVector.X, ActorVector.Y, ActorVector.Z);

	return CalcAngleBetweenVectors(ActorVector, ResVector);
}

FVector ABall::CalcRotVectorOnPlayerHit(AActor * OtherActor)
{
	FVector ActorVector, ResVector;
	ActorVector = GetActorForwardVector();

	// Reverse the Y value (old method)
	//ResVector = FVector(ActorVector.X, -ActorVector.Y, ActorVector.Z);

	// Get player's mesh size and origin
	FVector Origin, BoxExtent;
	OtherActor->GetActorBounds(true, Origin, BoxExtent);

	// Get X values of Origin and BoxExtent
	float OriginX = Origin.X;
	float BoxExtentX = BoxExtent.X;

	// Get Ball location
	float BallPosX = GetActorLocation().X;

	// Check if ball hit between max and min values
	if ((BallPosX < OriginX + BoxExtentX) &&
		(BallPosX > OriginX - BoxExtentX))
	{
		//// Calc normalized distance from player center
		//float distance = (BallPosX - OriginX) / BoxExtentX;

		//// Calc bounce angle and vector
		//float bounceAngle = distance * MaxBounceAngle;
		//FVector bounceVector;

		//Calc hit point
		float hitPoint = -(OriginX - BallPosX);
		float hitPointNormalized = hitPoint / BoxExtentX;
		float bounceAngle = hitPointNormalized * MaxBounceAngle;

		// Calc vector
		FVector vector;
		FRotator rotator;
		/*if (GetActorForwardVector().Y > 0.0f)
		{
			vector = FVector(0.0f, -1.0f, 0.0f);
			rotator = FRotator(0.0f, bounceAngle, 0.0f);
		}
		else
		{
			vector = FVector(0.0f, 1.0f, 0.0f);
			rotator = FRotator(0.0f, -bounceAngle, 0.0f);
		}*/

		if (GetActorForwardVector().Y > 0.0f)
		{
			vector = FVector(0.0f, -1.0f, 0.0f);
		}
		else
		{
			vector = FVector(0.0f, 1.0f, 0.0f);
		}
 
		if (bounceAngle < 0.0f)
		{
			bounceAngle = 360.0f + bounceAngle;
		}

		rotator = FRotator(0.0f, bounceAngle, 0.0f);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::SanitizeFloat(bounceAngle));
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *rotator.ToString());
		ResVector = rotator.RotateVector(vector);

		//if (vector.Y < 0.0f) ResVector = FVector(-ResVector.X, ResVector.Y, ResVector.Z);


		//ResVector = FVector(-FMath::Sin(bounceAngle), FMath::Cos(bounceAngle), ActorVector.Z);
	}
	// If not, use same logic as walls
	else
	{
		ResVector = FVector(-ActorVector.X, ActorVector.Y, ActorVector.Z);
	}

	return ResVector;
}

float ABall::CalcAngleBetweenVectors(FVector Vector1, FVector Vector2)
{	
	Vector1.Normalize();
	Vector2.Normalize();
	return FMath::RadiansToDegrees(acosf(FVector::DotProduct(Vector1, Vector2)));
}

void ABall::DebugMsg(FString msg)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%s"), *msg));
	}
}



