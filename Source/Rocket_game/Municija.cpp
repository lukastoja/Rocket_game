// Fill out your copyright notice in the Description page of Project Settings.


#include "Municija.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "Rocket_gamePawn.h"
#include "Components/SceneComponent.h"
#include "Prateci_zid.h"

// Sets default values
AMunicija::AMunicija()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshMetak = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshMetak");
	StaticMeshRaketa = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshRaketa");
	MaterialMunicija = CreateDefaultSubobject<UMaterial>("MaterialMunicija");

	municija_metak = 10;
	municija_raketa = 10;

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>("Box comp");
	MyBoxComponent->InitBoxExtent(FVector(100, 100, 100));
	MyBoxComponent->SetCollisionProfileName("Trigger");
	SetRootComponent(MyBoxComponent);
	StaticMesh->SetupAttachment(MyBoxComponent);
	StaticMeshMetak->SetupAttachment(MyBoxComponent);
	StaticMeshRaketa->SetupAttachment(MyBoxComponent);

	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMunicija::OnOverlapBegin);

	okretanje = FRotator(0.f, 0.f, 0.f);

	StaticMesh->SetWorldRotation(okretanje);
	StaticMeshMetak->SetWorldRotation(okretanje);
	StaticMeshRaketa->SetWorldRotation(okretanje);
	koliko = 2.f;
	rotacija = 0;
}

void AMunicija::SetMunicija(int metak, int raketa)
{
	municija_metak = metak;
	municija_raketa = raketa;

	if (municija_raketa > 0)
	{
		StaticMeshMetak->SetVisibility(false);
		StaticMeshRaketa->SetVisibility(true);
	}
	else
	{
		StaticMeshRaketa->SetVisibility(false);
		StaticMeshMetak->SetVisibility(true);
	}
}

int AMunicija::GetMetak()
{
	return municija_metak;
}

int AMunicija::GetRaketa()
{
	return municija_raketa;
}


// Called when the game starts or when spawned
void AMunicija::BeginPlay()
{
	Super::BeginPlay();

	municija_metak = 10;
	municija_raketa = 10;
}

// Called every frame
void AMunicija::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	rotacija = rotacija + koliko;
	if (rotacija > 360.f || rotacija < -360)
	{
		rotacija = 0;
	}
	okretanje = FRotator(0.f, rotacija, 0.f);

	StaticMesh->SetWorldRotation(okretanje);
	StaticMeshMetak->SetWorldRotation(okretanje);
	StaticMeshRaketa->SetWorldRotation(okretanje);

	test = 10;
}

void AMunicija::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARocket_gamePawn>(OtherActor) != nullptr)
	{
		Cast<ARocket_gamePawn>(OtherActor)->UpdateBr_metaka(municija_metak, municija_raketa);
		Destroy();
	}

	if (Cast<APrateci_zid>(OtherActor) != nullptr)
	{
		Destroy();
	}
}