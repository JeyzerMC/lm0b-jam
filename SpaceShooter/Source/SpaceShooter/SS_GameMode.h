// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Sound/SoundCue.h"
#include "SS_GameMode.generated.h"

class ASS_Asteroid;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpaceshipDestroyed);

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API ASS_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASS_GameMode();

	// Called every frame
	virtual void Tick(float deltaTime) override;

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
		FSpaceshipDestroyed OnSpaceshipDestroyed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ASS_Asteroid> Asteroid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxSpawnInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinSpawnInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float IncreaseSpawnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AsteroidsPerInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BaseAsteroidMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxAsteroidMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float IncreaseAsteroidSpeedRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundCue* BackgroundMusic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundCue* GameOverMusic;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnAsteroid();

	float m_CurrentAsteroidMoveSpeed;

	float m_CurrentSpawnInterval;

	float m_SpawnTimer;

	UAudioComponent* m_BGM;

	UFUNCTION()
		void OnGameEnd();
};
