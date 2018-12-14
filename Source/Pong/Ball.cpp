// Fill out your copyright notice in the Description page of Project Settings.

#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	//SphereCollider = CreateDefaultSubobject<USphereComponent>("SphereCollider");

	StaticMesh->BodyInstance.SetCollisionProfileName("OverlapAll");
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnOverlapBegin);
	StaticMesh->OnComponentEndOverlap.AddDynamic(this, &ABall::OnOverlapEnd);


	/*StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetNotifyRigidBodyCollision(true);
	StaticMesh->BodyInstance.SetCollisionProfileName("Pawn");
	StaticMesh->OnComponentHit.AddDynamic(this, &ABall::OnComponentHit);*/

	/*SphereCollider->SetSimulatePhysics(true);
	SphereCollider->SetNotifyRigidBodyCollision(true);
	SphereCollider->BodyInstance.SetCollisionProfileName("Pawn");
	SphereCollider->OnComponentHit.AddDynamic(this, &ABall::OnComponentHit);*/
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.X += BallSpeed * DeltaTime;
		NewLocation.Y += BallSpeed * DeltaTime;

		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABall::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		isMoving = false;
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(*OtherActor->GetName()));
	}
}

void ABall::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}
