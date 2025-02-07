// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Asteroid.h"
#include "SS_Widget_HUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

// Sets default values
ASS_Asteroid::ASS_Asteroid()
	: MovementSpeed(0.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Asteroid = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("SM Asteroid"));
	RootComponent = SM_Asteroid;

	SM_Asteroid->SetEnableGravity(false);
	SM_Asteroid->SetConstraintMode(EDOFMode::XYPlane);
	SM_Asteroid->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Asteroid->SetCollisionProfileName(TEXT("Destructible"));
	SM_Asteroid->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Overlap);
	SM_Asteroid->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void ASS_Asteroid::BeginPlay()
{
	Super::BeginPlay();
	SM_Asteroid->OnComponentBeginOverlap.AddDynamic(this, &ASS_Asteroid::OnOverlapBegin);

	auto idx = FMath::RandRange(0, Meshes.Num() - 1);
	SM_Asteroid->SetStaticMesh(Meshes[idx]);

	idx = FMath::RandRange(0, Materials.Num() - 1);
	SM_Asteroid->SetMaterial(0, Materials[idx]);
	m_RotationAxis = FRotator(FMath::FRandRange(-90.f, 90.f), FMath::FRandRange(-90.f, 90.f), FMath::FRandRange(-90.f, 90.f));
	m_RotationSpeed = FMath::FRandRange(0.5f, 3.f);
}

// Called every frame
void ASS_Asteroid::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	// Move to the left
	auto loc = GetActorLocation();
	auto dir = FVector(0.0f, -1.0f, 0.0f);

	AddActorLocalRotation(m_RotationAxis * deltaTime * m_RotationSpeed);
	
	SetActorLocation(loc + deltaTime * MovementSpeed * dir);

	if (!CheckBoundary()) {
		Destroy();
	}
}

void ASS_Asteroid::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherComp->GetCollisionObjectType() == ECC_PhysicsBody) {
		UpdateScore();
		Destroy();
	}
}

bool ASS_Asteroid::CheckBoundary()
{
	FVector2D screen_pos;

	auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->ProjectWorldLocationToScreen(GetActorLocation(), screen_pos, true);

	FVector2D vp_size;
	GEngine->GameViewport->GetViewportSize(vp_size);

	if (screen_pos.X < 0) {
		return false;
	}

	return true;
}

void ASS_Asteroid::UpdateScore()
{
	TArray<UUserWidget*> widgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), widgets, USS_Widget_HUD::StaticClass());

	auto widget = Cast<USS_Widget_HUD>(widgets[0]);

	if (DeathParticles.Num() > 0 && DeathParticles.Num() == ParticleScales.Num()) {
		int idx = FMath::RandRange(0, DeathParticles.Num() - 1);
		auto particle = DeathParticles[idx];
		auto transform = GetActorTransform();
		transform.SetScale3D(FVector(ParticleScales[idx]));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, transform);
	}

	if (widget) {
		widget->OnAsteroidDestroyed.Broadcast();
	}
}