// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_Asteroid.h"
#include "Kismet/GameplayStatics.h"

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
}

// Called every frame
void ASS_Asteroid::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	// Move to the left
	auto loc = GetActorLocation();
	auto dir = FVector(0.0f, -1.0f, 0.0f);
	
	SetActorLocation(loc + deltaTime * MovementSpeed * dir);

	if (!CheckBoundary()) {
		Destroy();
	}
}

void ASS_Asteroid::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherComp->GetCollisionObjectType() == ECC_PhysicsBody) {
		UE_LOG(LogTemp, Warning, TEXT("Asteroid shot down"));
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