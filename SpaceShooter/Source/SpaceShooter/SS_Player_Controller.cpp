// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Player_Controller.h"
#include "SS_SpaceCraft.h"
#include "SS_Projectile.h"
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

	InputComponent->BindAction("Dash", IE_Pressed, this, &ASS_Player_Controller::Dash);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &ASS_Player_Controller::Shoot);
}

void ASS_Player_Controller::MoveVertical(float value)
{
	auto pawn = Cast<ASS_SpaceCraft>(GetPawn());

	if (pawn && CheckBoundaries(pawn, 1, value)) {
		pawn->MoveVertical(value);
	}
}

void ASS_Player_Controller::MoveHorizontal(float value)
{
	auto pawn = Cast<ASS_SpaceCraft>(GetPawn());

	if (pawn && CheckBoundaries(pawn, 0, value)) {
		pawn->MoveHorizontal(value);
	}
}

void ASS_Player_Controller::Dash()
{
}

void ASS_Player_Controller::Shoot()
{
	auto pawn = Cast<ASS_SpaceCraft>(GetPawn());

	auto spawn_pos = pawn->GetActorLocation() + pawn->GetActorRightVector() * 100.f;
	auto spawn_rot = FRotator(0.0f);
	FActorSpawnParameters spawn_params;
	GetWorld()->SpawnActor<ASS_Projectile>(Projectile_BP, spawn_pos, spawn_rot, spawn_params);
	UE_LOG(LogTemp, Warning, TEXT("SHOOTING"));
}

bool ASS_Player_Controller::CheckBoundaries(AActor* pawn, int axis, float value)
{
	auto screen_pos = GetViewportPosition(pawn);

	if (axis == 1) {
		value = -1 * value;
	}

	if (value < 0 && screen_pos[axis] < EDGE_DISTANCE) {
		return false;
	}

	FVector2D vp_size;
	GEngine->GameViewport->GetViewportSize(vp_size);

	if (value > 0 && screen_pos[axis] > vp_size[axis] - EDGE_DISTANCE) {
		return false;
	}

	return true;
}

FVector2D ASS_Player_Controller::GetViewportPosition(AActor* pawn)
{
	FVector2D screen_pos;

	ProjectWorldLocationToScreen(pawn->GetActorLocation(), screen_pos, true);

	return screen_pos;
}
