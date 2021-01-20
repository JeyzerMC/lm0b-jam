// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SS_Player_Controller.generated.h"

class ASS_SpaceCraft;
class ASS_Projectile;
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

	void Dash();

	void Shoot();

	UPROPERTY(EditAnywhere)
		TSubclassOf<ASS_Projectile> Projectile_BP;

private:
	bool CheckBoundaries(AActor* pawn, int axis, float value);

	FVector2D GetViewportPosition(AActor* pawn);
};
