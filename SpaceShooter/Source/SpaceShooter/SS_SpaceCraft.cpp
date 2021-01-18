// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_SpaceCraft.h"

// Sets default values
ASS_SpaceCraft::ASS_SpaceCraft()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASS_SpaceCraft::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASS_SpaceCraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Konichiwa"));
}

// Called to bind functionality to input
void ASS_SpaceCraft::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

