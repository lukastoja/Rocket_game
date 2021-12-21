// Fill out your copyright notice in the Description page of Project Settings.


#include "TunelGore.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Rocket_gameGameMode.h"
#include "Rocket_gamePawn.h"

// Sets default values
ATunelGore::ATunelGore()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(SceneComponent);

	TunelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TunelMesh"));
	TunelMesh->SetupAttachment(SceneComponent);

	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Attach Point"));
	AttachPoint->SetupAttachment(SceneComponent);

	SpawnPoint1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Point1"));
	SpawnPoint1->SetupAttachment(SceneComponent);

	SpawnPoint2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Point2"));
	SpawnPoint2->SetupAttachment(SceneComponent);

	SpawnPoint3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Point3"));
	SpawnPoint3->SetupAttachment(SceneComponent);

	TurretSpawnPoint1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Turret Spawn Point1"));
	TurretSpawnPoint1->SetupAttachment(SceneComponent);

	MaterialTunel = CreateDefaultSubobject<UMaterial>("MaterialTunel");

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(SceneComponent);
	TriggerBox->SetBoxExtent(FVector(32.f, 500.f, 200.f));
	TriggerBox->SetCollisionProfileName(TEXT("OverlapAllDynamics"));
}

// Called when the game starts or when spawned
void ATunelGore::BeginPlay()
{
	Super::BeginPlay();

	RocketGameMode = Cast<ARocket_gameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	check(RocketGameMode);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATunelGore::OnOverlapBegin);
}

// Called every frame
void ATunelGore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FTransform ATunelGore::GetAttachTransform()
{
	// TODO: insert return statement here
	return AttachPoint->GetComponentTransform();
}

FTransform ATunelGore::GetSpawnPoint1()
{
	// TODO: insert return statement here
	return SpawnPoint1->GetComponentTransform();
}

FTransform ATunelGore::GetSpawnPoint2()
{
	// TODO: insert return statement here
	return SpawnPoint2->GetComponentTransform();
}

FTransform ATunelGore::GetSpawnPoint3()
{
	// TODO: insert return statement here
	return SpawnPoint3->GetComponentTransform();
}

FTransform ATunelGore::GetTurretSpawnPoint1()
{
	// TODO: insert return statement here
	return TurretSpawnPoint1->GetComponentTransform();
}

void ATunelGore::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARocket_gamePawn* character = Cast<ARocket_gamePawn>(OtherActor);

	if (character)
	{
		RocketGameMode->AddTunelTile();

		GetWorldTimerManager().SetTimer(DestroyHandle, this, &ATunelGore::DestroyTunelTile, 2.f, false); //2 sec
	}
}

void ATunelGore::DestroyTunelTile()
{
	if (DestroyHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyHandle);
	}

	this->Destroy();
}
