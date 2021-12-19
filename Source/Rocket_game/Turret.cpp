// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Components/SphereComponent.h"
#include "Rocket.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Rocket_gamePawn.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh1 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh1");
	StaticMesh2 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh2");
	StaticMesh3 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh3");
	StaticMesh4 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh4");

	SetRootComponent(StaticMesh1);
	StaticMesh2->SetupAttachment(StaticMesh1);
	StaticMesh3->SetupAttachment(StaticMesh2);
	StaticMesh4->SetupAttachment(StaticMesh3);

}


// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
