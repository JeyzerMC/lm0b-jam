// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_StaticDecoration.h"

// Sets default values
ASS_StaticDecoration::ASS_StaticDecoration()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_StaticDeco = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("SM Asteroid"));
	RootComponent = SM_StaticDeco;

	SM_StaticDeco->SetEnableGravity(false);
	SM_StaticDeco->SetConstraintMode(EDOFMode::XYPlane);
}

// Called when the game starts or when spawned
void ASS_StaticDecoration::BeginPlay()
{
	Super::BeginPlay();
	
	m_RotationAxis = FRotator(FMath::FRandRange(-90.f, 90.f), FMath::FRandRange(-90.f, 90.f), FMath::FRandRange(-90.f, 90.f));
	m_RotationSpeed = FMath::FRandRange(0.3f, 0.8f);
}

// Called every frame
void ASS_StaticDecoration::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AddActorLocalRotation(m_RotationAxis * deltaTime * m_RotationSpeed);
}

