// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_SpaceCraft.h"
#include "Kismet/GameplayStatics.h"
#include "SS_GameMode.h"

// Sets default values
ASS_SpaceCraft::ASS_SpaceCraft()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto DefaultSceneRoot = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;

	SM_Spacecraft = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("SM Spacecraft"));
	SM_Spacecraft->SetupAttachment(DefaultSceneRoot);

	SM_Spacecraft->SetEnableGravity(false);
	SM_Spacecraft->SetConstraintMode(EDOFMode::XYPlane);
	SM_Spacecraft->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Spacecraft->SetCollisionProfileName(TEXT("Vehicle"));
	SM_Spacecraft->SetCollisionResponseToChannel(ECC_Destructible, ECollisionResponse::ECR_Overlap);
	SM_Spacecraft->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);

	FloatingComp = CreateAbstractDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Movement"));
}

void ASS_SpaceCraft::BeginPlay()
{
	Super::BeginPlay();

	SM_Spacecraft->OnComponentBeginOverlap.AddDynamic(this, &ASS_SpaceCraft::OnOverlapBegin);
}

// Called to bind functionality to input
void ASS_SpaceCraft::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
}

void ASS_SpaceCraft::MoveVertical(float value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value);
}

void ASS_SpaceCraft::MoveHorizontal(float value)
{
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), value);
}

void ASS_SpaceCraft::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherComp->GetCollisionObjectType() == ECC_Destructible) {
		//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		//UE_LOG(LogTemp, Warning, TEXT("Crashed into asteroid"));
		auto gm = Cast<ASS_GameMode>(GetWorld()->GetAuthGameMode());
		gm->OnSpaceshipDestroyed.Broadcast();
		Destroy();
	}
}
