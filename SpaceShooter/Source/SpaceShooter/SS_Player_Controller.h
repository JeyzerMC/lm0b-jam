// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SS_Player_Controller.generated.h"

class ASS_SpaceCraft;
/**
 * 
 */
UCLASS()
class SPACESHOOTER_API ASS_Player_Controller : public APlayerController
{
	GENERATED_BODY()

		ASS_Player_Controller();

	UFUNCTION()
		virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;

	void MoveVertical(float value);

	void MoveHorizontal(float value);

private:
	FVector2D GetViewportPosition(ASS_SpaceCraft* pawn);

	bool CheckBoundaries(int axis, float value);
};
