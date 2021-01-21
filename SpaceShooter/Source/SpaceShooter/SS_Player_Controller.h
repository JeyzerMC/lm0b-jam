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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Cooldown;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;

	void MoveVertical(float value);

	void MoveHorizontal(float value);

	void Dash();

	void Shoot();

	UPROPERTY(EditAnywhere)
		TSubclassOf<ASS_Projectile> Projectile_BP;

	int m_NBullets;

	int m_RemainingBullets;

private:
	bool CheckBoundaries(AActor* pawn, int axis, float value);

	FVector2D GetViewportPosition(AActor* pawn);

	void EmitBulletRecharges(bool recharged);

	UFUNCTION()
		virtual void SetupInputComponent() override;

	TArray<float> m_Recharges;
};
