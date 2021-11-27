// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Components/SphereComponent.h"
#include "Rocket.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Engine.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	radius = 1000;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");

	MySphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere comp");
	MySphereComponent->InitSphereRadius(radius);

	SetRootComponent(MySphereComponent);
	StaticMesh->SetupAttachment(MySphereComponent);

	MySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnOverlapBegin);
	MySphereComponent->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnOverlapEnd);
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

void ATurret::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARocket>(OtherActor) != nullptr)
	{
		if (!Cast<ARocket>(OtherActor)->targetSet)
		{
			Cast<ARocket>(OtherActor)->targetPos = GetActorLocation();
			Cast<ARocket>(OtherActor)->targetSet = true;
			Cast<ARocket>(OtherActor)->boundingBoxEntrancerPoint = Cast<ARocket>(OtherActor)->GetActorLocation();
		}
	}
}

void ATurret::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARocket>(OtherActor) != nullptr)
	{
		Cast<ARocket>(OtherActor)->Destroy();
	}
}

