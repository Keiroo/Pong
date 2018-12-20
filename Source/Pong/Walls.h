#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Walls.generated.h"

UCLASS()
class PONG_API AWalls : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:	
	AWalls();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WallMesh;
};
