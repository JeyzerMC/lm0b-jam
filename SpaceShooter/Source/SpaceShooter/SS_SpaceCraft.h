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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* SM_Spacecraft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Space")
		UFloatingPawnMovement* FloatingComp;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	virtual void MoveVertical(float value);

	virtual void MoveHorizontal(float value);
};
