// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_GameMode.h"
#include "SS_Asteroid.h"
#include "Kismet/GameplayStatics.h"

ASS_GameMode::ASS_GameMode()
{
}

void ASS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Testo"));
	m_CurrentAsteroidMoveSpeed = BaseAsteroidMoveSpeed;
	SpawnAsteroid();
}

void ASS_GameMode::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ASS_GameMode::SpawnAsteroid()
{
	for (int i = 0; i < AsteroidsPerInterval; i++) {
		float pos_X = FMath::RandRange(-1000.f, 1000.f);
		float pos_Y = FMath::RandRange(3000.f, 5000.f);

		auto asteroid = GetWorld()->SpawnActor<ASS_Asteroid>(Asteroid, FVector(pos_X, pos_Y, 0), FRotator(0.0f, 0.0f, 0.0f));
		asteroid->MovementSpeed = FMath::RandRange(0.8f * m_CurrentAsteroidMoveSpeed, 1.2f * m_CurrentAsteroidMoveSpeed);
	}
}