// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Player_Controller.h"
#include "SS_SpaceCraft.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

constexpr float EDGE_DISTANCE = 50.f;

ASS_Player_Controller::ASS_Player_Controller()
{
}

void ASS_Player_Controller::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> cameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), cameras);

	FViewTargetTransitionParams params;
	SetViewTarget(cameras[0], params);
}

void ASS_Player_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);

	InputComponent->BindAxis("MoveVertical", this, &ASS_Player_Controller::MoveVertical);
	InputComponent->BindAxis("MoveHorizontal", this, &ASS_Player_Controller::MoveHorizontal);
}

void ASS_Player_Controller::MoveVertical(float value)
{
	auto pawn = Cast<ASS_SpaceCraft>(GetPawn());

	if (!pawn)
		return;

	auto screen_pos = GetViewportPosition(pawn);

	if (value > 0 && screen_pos.Y < EDGE_DISTANCE) {
		return;
	}

	FVector2D vp_size;
	GEngine->GameViewport->GetViewportSize(vp_size);

	if (value < 0 && screen_pos.Y > vp_size.Y - EDGE_DISTANCE) {
		return;
	}

	pawn->MoveVertical(value);
}

void ASS_Player_Controller::MoveHorizontal(float value)
{
	auto pawn = Cast<ASS_SpaceCraft>(GetPawn());

	if (!pawn)
		return;

	auto screen_pos = GetViewportPosition(pawn);

	if (value < 0 && screen_pos.X < EDGE_DISTANCE) {
		return;
	}

	FVector2D vp_size;
	GEngine->GameViewport->GetViewportSize(vp_size);

	if (value > 0 && screen_pos.X > vp_size.X - EDGE_DISTANCE) {
		return;
	}

	pawn->MoveHorizontal(value);
}

FVector2D ASS_Player_Controller::GetViewportPosition(ASS_SpaceCraft* pawn)
{
	FVector2D screen_pos;

	ProjectWorldLocationToScreen(pawn->GetActorLocation(), screen_pos, true);

	return screen_pos;
}

bool ASS_Player_Controller::CheckBoundaries(int axis, float value)
{
	return false;
}
