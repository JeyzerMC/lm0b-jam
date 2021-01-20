// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include "Blueprint/UserWidget.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "SS_SpaceCraft.generated.h"

UCLASS()
class SPACESHOOTER_API ASS_SpaceCraft : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASS_SpaceCraft();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	virtual void MoveVertical(float value);

	virtual void MoveHorizontal(float value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* SM_Spacecraft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Space")
		UFloatingPawnMovement* FloatingComp;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
};
