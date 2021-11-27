// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Rocket_gamePawn.h"
#include "RocketGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Prateci_zid.h"
#include "TimerManager.h"

// Sets default values
APortal::APortal()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PortalUnutar;
		FConstructorStatics()
			: PortalUnutar(TEXT("/Game/Flying/Meshes/portal/portal_Circle"))
		{
		}
	};

	struct FConstructorStatics1
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PortalVani;
		FConstructorStatics1()
			: PortalVani(TEXT("/Game/Flying/Meshes/portal/portal_RotateKrugovi"))
		{
		}
	};

	struct FConstructorStatics2
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PortalTrokut;
		FConstructorStatics2()
			: PortalTrokut(TEXT("/Game/Flying/Meshes/portal/portal_RotateTrokuti"))
		{
		}
	};

	static FConstructorStatics ConstructorStatics;
	static FConstructorStatics1 ConstructorStatics1;
	static FConstructorStatics2 ConstructorStatics2;

	// Create static mesh component
	PortalUnutar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalUnutar"));
	PortalUnutar->SetStaticMesh(ConstructorStatics.PortalUnutar.Get());	// Set static mesh
	SetRootComponent(PortalUnutar);

	// Create static mesh component
	PortalVani = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalVani"));
	PortalVani->SetStaticMesh(ConstructorStatics1.PortalVani.Get());	// Set static mesh
	PortalVani->SetupAttachment(RootComponent);

	// Create static mesh component
	PortalTrokut = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalTrokut"));
	PortalTrokut->SetStaticMesh(ConstructorStatics2.PortalTrokut.Get());	// Set static mesh
	PortalTrokut->SetupAttachment(RootComponent);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetupAttachment(RootComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	x = 0;
	y = 0;
	z = 180;

	RootComponent->SetWorldRotation(FRotator(y,z,x));
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
}

void APortal::DestroyPortal()
{
	if (DestroyHandle.IsValid())
	{
		//GetWorldTimerManager().ClearTimer(DestroyHandle);
		GetWorld()->GetTimerManager().ClearTimer(DestroyHandle);
	}

	this->Destroy();
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	x = x + spin;
	if (x > 360 || x < -360)
	{
		x = 0;
	}

	RootComponent->SetWorldRotation(FRotator(y, z, x));
}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARocket_gamePawn>(OtherActor) != nullptr)
	{
		int score = Cast<ARocket_gamePawn>(OtherActor)->GetScoreInt();

		score = score + 5;

		Cast<ARocket_gamePawn>(OtherActor)->SetScore(score);
		//GetWorldTimerManager().SetTimer(DestroyHandle, this, &APortal::DestroyPortal, 2.f, false); //2 sec
		GetWorld()->GetTimerManager().SetTimer(DestroyHandle, this, &APortal::DestroyPortal, 2.f, true);
	}

	if (Cast<APrateci_zid>(OtherActor) != nullptr)
	{
		Destroy();
	}
}

