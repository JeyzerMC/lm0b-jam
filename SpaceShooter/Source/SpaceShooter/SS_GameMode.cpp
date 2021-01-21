// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_GameMode.h"
#include "SS_Asteroid.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

ASS_GameMode::ASS_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Testo"));
	m_CurrentAsteroidMoveSpeed = BaseAsteroidMoveSpeed;
	m_CurrentSpawnInterval = MinSpawnInterval;
	m_SpawnTimer = m_CurrentSpawnInterval;
	SpawnAsteroid();

	OnSpaceshipDestroyed.AddDynamic(this, &ASS_GameMode::OnGameEnd);

	//UGameplayStatics::Spawn(GetWorld(), BackgroundMusic);
	m_BGM = UGameplayStatics::SpawnSound2D(GetWorld(), BackgroundMusic);
	if (m_BGM) {
		m_BGM->Play();
	}
}

void ASS_GameMode::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (m_SpawnTimer < 0) {
		m_CurrentSpawnInterval -= m_CurrentSpawnInterval > MaxSpawnInterval? IncreaseSpawnRate : 0;
		m_SpawnTimer = m_CurrentSpawnInterval;
		m_CurrentAsteroidMoveSpeed += m_CurrentAsteroidMoveSpeed < MaxAsteroidMoveSpeed? IncreaseAsteroidSpeedRate: IncreaseAsteroidSpeedRate / 10.f;

		SpawnAsteroid();
	}

	m_SpawnTimer -= deltaTime;
}

void ASS_GameMode::SpawnAsteroid()
{
	for (int i = 0; i < AsteroidsPerInterval; i++) {
		float pos_X = FMath::RandRange(-1000.f, 1000.f);
		float pos_Y = FMath::RandRange(4000.f, 6000.f);

		auto asteroid = GetWorld()->SpawnActor<ASS_Asteroid>(Asteroid, FVector(pos_X, pos_Y, 0), FRotator(0.0f, 0.0f, 0.0f));
		asteroid->MovementSpeed = FMath::RandRange(0.8f * m_CurrentAsteroidMoveSpeed, 1.2f * m_CurrentAsteroidMoveSpeed);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Spawning!"));
}

void ASS_GameMode::OnGameEnd()
{
	if (m_BGM) {
		m_BGM->Stop();
	}
	UGameplayStatics::PlaySound2D(GetWorld(), GameOverMusic);
	UE_LOG(LogTemp, Warning, TEXT("Game finished in Game mode"));
}