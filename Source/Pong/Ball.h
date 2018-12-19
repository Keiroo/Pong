// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine/TriggerBox.h"
#include "Walls.h"
#include "MyPlayer.h"
#include "Ball.generated.h"

UCLASS()
class PONG_API ABall : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY()
	FVector movingDirection;

	UPROPERTY()
	bool hasHit = false;

	UPROPERTY()
	float hitTimer = 0.0f;

	UPROPERTY()
	float maxHitTimer = 0.2f;

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

	UPROPERTY(BlueprintReadWrite)
	bool isMoving = false;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BallMesh;

	UPROPERTY()
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere)
	float BallSpeed = 1.0f;

	UPROPERTY(EditAnywhere)
	float MaxBounceAngle = 75.0f;

	UPROPERTY(EditAnywhere)
	bool DebugPrint = false;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	void RotateOnHit(AActor* OtherActor);

	// True = Right, False = Left
	UFUNCTION(BlueprintCallable)
	void RandomRotate(bool direction);

	UFUNCTION()
	void ChangeDirectionOnWallHit();

	UFUNCTION()
	void ChangeDirectionOnPlayerHit(AActor* OtherActor);

	UFUNCTION()
	void PrintOnScreen(FString message);
};
