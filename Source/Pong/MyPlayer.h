#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Classes/Materials/Material.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyPlayer.generated.h"

UCLASS()
class PONG_API AMyPlayer : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float PlayerInput;

protected:
	virtual void BeginPlay() override;

public:	
	AMyPlayer();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* PlayerMesh;

	UPROPERTY(EditAnywhere, Category = Mesh)
	UMaterial* MeshMaterial;

	UPROPERTY()
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "2"))
	int PlayerNumber = 1;

	UFUNCTION(BlueprintCallable)
	void MovePlayer(float AxisValue);
};
