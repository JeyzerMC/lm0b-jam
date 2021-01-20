// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_AsteroidSpawner.h"
#include "SS_Asteroid.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ASS_AsteroidSpawner::ASS_AsteroidSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASS_AsteroidSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASS_AsteroidSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASS_AsteroidSpawner::SpawnAsteroid()
{
	FVector2D vp_size;
	GEngine->GameViewport->GetViewportSize(vp_size);

	//U
}