// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Walls.h"
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
	float speed = 1.0f;

	UPROPERTY(EditAnywhere, Category = HitNames)
	FString WallsName = "BP_Walls";

	UPROPERTY(EditAnywhere, Category = HitNames)
	FString PlayerName = "BP_Player";

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void RotateOnHit(AActor* OtherActor);

};
