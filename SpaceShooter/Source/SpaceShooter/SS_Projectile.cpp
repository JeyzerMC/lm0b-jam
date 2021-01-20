// Fill out your copyright notice in the Description page of Project Settings.

#include "SS_Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASS_Projectile::ASS_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Projectile = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("SM Projectile"));
	RootComponent = SM_Projectile;

	SM_Projectile->SetEnableGravity(false);
	SM_Projectile->SetConstraintMode(EDOFMode::XYPlane);
	SM_Projectile->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Projectile->SetCollisionProfileName(TEXT("PhysicsBody"));
	SM_Projectile->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Overlap);
	SM_Projectile->SetCollisionResponseToChannel(ECC_Destructible, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void ASS_Projectile::BeginPlay()
{
	Super::BeginPlay();

	SM_Projectile->OnComponentBeginOverlap.AddDynamic(this, &ASS_Projectile::OnOverlapBegin);
	SM_Projectile->AddImpulse(FVector(0.0f, 1.0f, 0.0f) * Impulse);
}

// Called every frame
void ASS_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CheckBoundary()) {
		Destroy();
	}
}

void ASS_Projectile::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherComp->GetCollisionObjectType() == ECC_Destructible) {
		UE_LOG(LogTemp, Warning, TEXT("Projectile reached target"));
	}
}

bool ASS_Projectile::CheckBoundary()
{
	FVector2D screen_pos;

	auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->ProjectWorldLocationToScreen(GetActorLocation(), screen_pos, true);

	FVector2D vp_size;
	GEngine->GameViewport->GetViewportSize(vp_size);

	if (screen_pos.X > vp_size.X) {
		return false;
	}

	return true;
}

