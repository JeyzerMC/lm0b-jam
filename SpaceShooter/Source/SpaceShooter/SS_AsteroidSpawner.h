// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SS_AsteroidSpawner.generated.h"

class ASS_Asteroid;

UCLASS()
class SPACESHOOTER_API ASS_AsteroidSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASS_AsteroidSpawner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ASS_Asteroid> Asteroid;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnAsteroid();
};
