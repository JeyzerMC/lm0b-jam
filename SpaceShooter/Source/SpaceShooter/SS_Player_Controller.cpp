// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Player_Controller.h"
#include "SS_SpaceCraft.h"
#include "SS_Projectile.h"
#include "SS_Widget_HUD.h"
#include "SS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

constexpr float EDGE_DISTANCE = 50.f;

ASS_Player_Controller::ASS_Player_Controller()
	: m_RemainingBullets(0), m_NBullets(5)
{
	m_RemainingBullets = m_NBullets;
}

void ASS_Player_Controller::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(false);
	TArray<AActor*> cameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), cameras);

	FViewTargetTransitionParams params;
	SetViewTarget(cameras[0], params);

	for (int i = 0; i < m_NBullets; i++) {
		m_Recharges.Add(1.f);
	}

	auto gm = Cast<ASS_GameMode>(GetWorld()->GetAuthGameMode());
	if (gm) {
		//gm->OnSpaceshipDestroyed.
		gm->OnSpaceshipDestroyed.AddDynamic(this, &ASS_Player_Controller::OnGameEnd);
	}
}

void ASS_Player_Controller::Tick(float deltaTime)
{
	bool recharged = false;
	for (int i = m_RemainingBullets; i < m_NBullets; i++) {
		if (m_Recharges[i] < 1.f) {
			m_Recharges[i] += deltaTime / Cooldown;
		}
		else {
			m_Recharges[i] = 1.f;
			m_RemainingBullets++;
			recharged = true;
		}
	}

	if (m_RemainingBullets < m_NBullets) {
		m_Recharges.Sort([](float a, float b) { return a > b; });
	}

	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, FString::Printf(TEXT("Remaining bullets: %d"), m_RemainingBullets));
	EmitBulletRecharges(recharged);
}

void ASS_Player_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);

	InputComponent->BindAxis("MoveVertical", this, &ASS_Player_Controller::MoveVertical);
	InputComponent->BindAxis("MoveHorizontal", this, &ASS_Player_Controller::MoveHorizontal);

	InputComponent->BindAction("Shoot", IE_Pressed, this, &ASS_Player_Controller::Shoot);
	InputComponent->BindAction("Dash", IE_Pressed, this, &ASS_Player_Controller::Dash);
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
	// TODO eventually
}

void ASS_Player_Controller::Shoot()
{
	if (m_RemainingBullets == 0)
		return;

	auto pawn = Cast<ASS_SpaceCraft>(GetPawn());

	auto spawn_pos = pawn->GetActorLocation() + pawn->GetActorRightVector() * 100.f;
	auto spawn_rot = FRotator(0.0f);
	FActorSpawnParameters spawn_params;
	GetWorld()->SpawnActor<ASS_Projectile>(Projectile_BP, spawn_pos, spawn_rot, spawn_params);
	m_Recharges[--m_RemainingBullets] = 0.f;
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

void ASS_Player_Controller::EmitBulletRecharges(bool recharged)
{
	TArray<UUserWidget*> widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), widgets, USS_Widget_HUD::StaticClass());

	auto widget = Cast<USS_Widget_HUD>(widgets[0]);

	if (widget) {
		widget->OnBulletRecharges.Broadcast(m_Recharges, recharged);
	}
}

void ASS_Player_Controller::OnGameEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Game End from Controller"));
	InputComponent->RemoveActionBinding(0);
	InputComponent->RemoveActionBinding(1);
	SetShowMouseCursor(true);
}
