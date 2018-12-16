// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Walls.h"
#include "MyPlayer.h"
#include "Ball.generated.h"

UCLASS()
class PONG_API ABall : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float Pitch = 0.0f;

	UPROPERTY()
	float Yaw = 0.0f;

	UPROPERTY()
	float Roll = 0.0f;

	UPROPERTY()
	bool isMoving = true;

	UPROPERTY()
	bool isOverlapping = false;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	ABall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BallMesh;

	UPROPERTY()
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere)
	float Speed = 1.0f;

	UPROPERTY(EditAnywhere)
	float MaxBounceAngle = 75.0f;

	UPROPERTY(EditAnywhere)
	bool DebugLog = false;

	UPROPERTY()
	float ActorZ;

	UFUNCTION()
	void RotateOnHit(AActor* OtherActor);

	UFUNCTION()
	void RandomRotate();

	UFUNCTION()
	float CalcRotAngleOnWallHit();

	UFUNCTION()
	FVector CalcRotVectorOnPlayerHit(AActor* OtherActor);

	UFUNCTION()
	float CalcAngleBetweenVectors(FVector Vector1, FVector Vector2);

	UFUNCTION()
	void DebugMsg(FString msg);

};
