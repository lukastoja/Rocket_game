// Fill out your copyright notice in the Description page of Project Settings.


#include "Prateci_zid.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Rocket_gamePawn.h"
#include "Bullet.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TunelLijevo.h"
#include "TunelDesno.h"
#include "TunelGore.h"
#include "TunelDole.h"

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
	flag = true;
	
}

// Called every frame
void APrateci_zid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector lokacija_pawn = Cast<ARocket_gamePawn>(player)->GetActorLocation();
	FRotator actorRotation = GetActorRotation();

	FLatentActionInfo LatentInfo; 
	LatentInfo.CallbackTarget = this;
	//UKismetSystemLibrary::MoveComponentTo(RootComponent, lokacija_pawn, actorRotation, false, false, 1.5f, true, EMoveComponentAction::Type::Move, LatentInfo);

	if (flag)
	{
		int x = GetActorLocation().X;
		x = x + 100;
		FVector location = GetActorLocation();
		location.X = x;
		SetActorLocation(location);
	}
}

void APrateci_zid::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARocket_gamePawn>(OtherActor) != nullptr)
	{
		Cast<ARocket_gamePawn>(OtherActor)->Destroy_Pawn();
	}

	if (Cast<ATunelDesno>(OtherActor) != nullptr)
	{
		FTransform finalDest = Cast<ATunelDesno>(OtherActor)->GetAttachTransform();
		FVector finalLocation = finalDest.GetLocation();
		FRotator finalRotation = finalDest.GetRotation().Rotator();
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(RootComponent, finalLocation, finalRotation, false, false, 10.f, true, EMoveComponentAction::Type::Move, LatentInfo);
		flag = false;
	}
	if (Cast<ATunelDole>(OtherActor) != nullptr)
	{
		FTransform finalDest = Cast<ATunelDole>(OtherActor)->GetAttachTransform();
		FVector finalLocation = finalDest.GetLocation();
		FRotator finalRotation = finalDest.GetRotation().Rotator();
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(RootComponent, finalLocation, finalRotation, false, false, 10.f, true, EMoveComponentAction::Type::Move, LatentInfo);
		flag = false;
	}
	if (Cast<ATunelGore>(OtherActor) != nullptr)
	{
		FTransform finalDest = Cast<ATunelGore>(OtherActor)->GetAttachTransform();
		FVector finalLocation = finalDest.GetLocation();
		FRotator finalRotation = finalDest.GetRotation().Rotator();
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(RootComponent, finalLocation, finalRotation, false, false, 10.f, true, EMoveComponentAction::Type::Move, LatentInfo);
		flag = false;
	}
	if (Cast<ATunelLijevo>(OtherActor) != nullptr)
	{
		FTransform finalDest = Cast<ATunelLijevo>(OtherActor)->GetAttachTransform();
		FVector finalLocation = finalDest.GetLocation();
		FRotator finalRotation = finalDest.GetRotation().Rotator();
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(RootComponent, finalLocation, finalRotation, false, false, 10.f, true, EMoveComponentAction::Type::Move, LatentInfo);
		flag = false;
	}
}
