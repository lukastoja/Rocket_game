// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Components/SphereComponent.h"
#include "Rocket.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "Rocket_gamePawn.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	radius = 1000;
	sensingRange = 3000;
	currentDistance = sensingRange + 2;
	TraceDistance = 3000;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");

	MySphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere comp");
	MySphereComponent->InitSphereRadius(radius);

	MySphereComponentSensing = CreateDefaultSubobject<USphereComponent>("Sphere comp sensing");
	MySphereComponentSensing->InitSphereRadius(sensingRange);

	SetRootComponent(MySphereComponent);
	StaticMesh->SetupAttachment(MySphereComponent);
	MySphereComponentSensing->SetupAttachment(MySphereComponent);

	MySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnOverlapBegin);
	MySphereComponent->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnOverlapEnd);

	MySphereComponentSensing->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnOverlapBeginSensing);
}

void ATurret::FindBestTarget()
{
	float bestDistance = sensingRange + 1;
	AActor* bestTarget;
	UE_LOG(LogTemp, Warning, TEXT("nešto jede govna"));
	if (currentDistance < bestDistance)
	{
		//line of sight 
		FHitResult Hit;

		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), currentTarget->GetActorLocation(), ECC_Visibility, RV_TraceParams);
		DrawDebugLine(GetWorld(), GetActorLocation(), currentTarget->GetActorLocation(), FColor::Orange, false, 2.0f);
		UE_LOG(LogTemp, Warning, TEXT("pogodio sam nešto drugo vjv"));
		if (Cast<ARocket_gamePawn>(Hit.GetActor()) != nullptr)
		{
			DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(5, 5, 5), FColor::Emerald, false, 2.0f);
			UE_LOG(LogTemp, Warning, TEXT("okej tu sam kako treba"));
			bestTarget = currentTarget;
			bestDistance = currentDistance;
			//neka puca u tom smjeru
		}
	}
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

	FindBestTarget();
}

void ATurret::OnOverlapBeginSensing(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ARocket_gamePawn>(OtherActor) != nullptr)
	{
		currentTarget = OtherActor;
		currentDistance = FVector::Dist(GetActorLocation(), currentTarget->GetActorLocation());
	}
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

	if (Cast<ARocket_gamePawn>(OtherActor) != nullptr)
	{
		currentTarget = OtherActor;
		currentDistance = FVector::Dist(GetActorLocation(), currentTarget->GetActorLocation());
	}
}

void ATurret::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ARocket>(OtherActor) != nullptr)
	{
		Cast<ARocket>(OtherActor)->Destroy();
	}
}

