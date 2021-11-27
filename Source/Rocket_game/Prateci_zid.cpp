// Fill out your copyright notice in the Description page of Project Settings.


#include "Prateci_zid.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Rocket_gamePawn.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APrateci_zid::APrateci_zid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create static mesh component
	zid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Zid_Mesh"));
	SetRootComponent(zid);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetupAttachment(RootComponent);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APrateci_zid::OnOverlapBegin);
}

// Called when the game starts or when spawned
void APrateci_zid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APrateci_zid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector lokacija = GetActorLocation();
	int x = lokacija.X;
	APawn * test = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector lokacija_pawn = Cast<ARocket_gamePawn>(test)->GetActorLocation();

	int x1 = lokacija_pawn.X;

	if (abs(x1 - x) > udaljenost)
	{
		lokacija.X = lokacija.X + x1 - x - udaljenost;
	}

	SetActorLocation(lokacija);
}

void APrateci_zid::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARocket_gamePawn>(OtherActor) != nullptr)
	{
		Cast<ARocket_gamePawn>(OtherActor)->Destroy_Pawn();
	}
}
