// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SS_Widget_HUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsteroidDestroyed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBulletRecharges, const TArray<float>&, bulletRecharges, bool, recharged);

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API USS_Widget_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
		FAsteroidDestroyed OnAsteroidDestroyed;

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
		FBulletRecharges OnBulletRecharges;
};
