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
	/*radius = 1000;
	sensingRange = 3000;
	currentDistance = sensingRange + 2;
	TraceDistance = 3000;*/

	StaticMesh1 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh1");
	StaticMesh2 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh2");
	StaticMesh3 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh3");

	/*MySphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere comp");
	MySphereComponent->InitSphereRadius(radius);*/

	/*MySphereComponentSensing = CreateDefaultSubobject<USphereComponent>("Sphere comp sensing");
	MySphereComponentSensing->InitSphereRadius(sensingRange);*/

	SetRootComponent(StaticMesh1);
	//MySphereComponent->SetupAttachment(StaticMesh1);
	StaticMesh2->SetupAttachment(StaticMesh1);
	StaticMesh3->SetupAttachment(StaticMesh2);
	//MySphereComponentSensing->SetupAttachment(StaticMesh);

	/*MySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnOverlapBegin);
	MySphereComponent->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnOverlapEnd);

	//MySphereComponentSensing->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnOverlapBeginSensing);
	okretanje = FRotator(0.f, 0.f, 0.f);
	StaticMesh1->SetWorldRotation(okretanje);
	kolikox = 2.f;
	kolikoy = 2.f;
	kolikoz = 2.f;
	rotacijax = 0;
	rotacijay = 0;
	rotacijaz = 0;*/
}

/*bool ATurret::FindBestTarget()
{
	float bestDistance = sensingRange + 1;
	AActor* bestTarget;
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

			return true;
		}
	}

	return false;
}

void ATurret::SetTurretRotation(float DeltaTime)
{
	float dot = FVector::DotProduct(GetActorLocation(), currentTarget->GetActorLocation());
	float sizea = GetActorLocation().Size();
	float sizeb = currentTarget->GetActorLocation().Size();

	float cosAlpha = dot / (sizea * sizeb);


}*/

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (FindBestTarget())
	{
		// jebemu mu mater actor se ne okrece
		UE_LOG(LogTemp, Warning, TEXT("nešto jede govna"));
		SetTurretRotation(DeltaTime);
	}*/
	/*rotacijax = rotacijax + kolikox;
	rotacijay = rotacijay + kolikoy;
	rotacijaz = rotacijaz + kolikoz;
	if (rotacijax > 360.f || rotacijax < -360)
	{
		rotacijax = 0;
	}
	if (rotacijay > 360.f || rotacijay < -360)
	{
		rotacijay = 0;
	}
	if (rotacijaz > 360.f || rotacijaz < -360)
	{
		rotacijaz = 0;
	}
	okretanje = FRotator(rotacijay, rotacijaz, rotacijax);

	StaticMesh->SetWorldRotation(okretanje);*/
}

/*void ATurret::OnOverlapBeginSensing(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
}*/

