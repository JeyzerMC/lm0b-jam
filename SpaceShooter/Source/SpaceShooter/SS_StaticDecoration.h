// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SS_StaticDecoration.generated.h"

UCLASS()
class SPACESHOOTER_API ASS_StaticDecoration : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASS_StaticDecoration();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* SM_StaticDeco;

	virtual void Tick(float deltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FRotator m_RotationAxis;

	float m_RotationSpeed;
};
