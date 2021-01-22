// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "SS_Asteroid.generated.h"

UCLASS()
class SPACESHOOTER_API ASS_Asteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASS_Asteroid();

	// Called every frame
	virtual void Tick(float deltaTime) override;

	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UStaticMesh*> Meshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UMaterialInstance*> Materials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UParticleSystem*> DeathParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> ParticleScales;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Asteroid;

private:
	bool CheckBoundary();

	void UpdateScore();

	FRotator m_RotationAxis;

	float m_RotationSpeed;
};
