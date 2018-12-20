#include "Walls.h"

AWalls::AWalls()
{
	PrimaryActorTick.bCanEverTick = false;
	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>("WallMesh");
}

void AWalls::BeginPlay()
{
	Super::BeginPlay();	
}

void AWalls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

