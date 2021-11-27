// Fill out your copyright notice in the Description page of Project Settings.


#include "Prepreka_zid.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Rocket_gamePawn.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "Prateci_zid.h"
#include "Rocket.h"

// Sets default values
APrepreka_zid::APrepreka_zid()
{
	// Create static mesh component
	zid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Zid_Mesh"));
	SetRootComponent(zid);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetupAttachment(RootComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APrepreka_zid::OnOverlapBegin);
	health = 3;

	MoveScale = 200.f;
}

void APrepreka_zid::SetHealth(int hp)
{
	health = hp;
}

int APrepreka_zid::GetHealth()
{
	return health;
}

void APrepreka_zid::SetMovement(float x1, float y1, float z1)
{
	x = x1;
	y = y1;
	z = z1;
}

// Called when the game starts or when spawned
void APrepreka_zid::BeginPlay()
{
	Super::BeginPlay();
	
	MoveDirection = FVector(x, y, z);
}

// Called every frame
void APrepreka_zid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveDirection = FVector(x, y, z);
	FVector MoveDelta = (MoveDirection * (FMath::Sin(GetWorld()->GetTimeSeconds() + DeltaTime) - FMath::Sin(GetWorld()->GetTimeSeconds()))) * MoveScale;
	AddActorWorldOffset(MoveDelta, true);
}

void APrepreka_zid::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARocket_gamePawn>(OtherActor) != nullptr)
	{
		Cast<ARocket_gamePawn>(OtherActor)->Destroy_Pawn();
	}

	if (Cast<ABullet>(OtherActor) != nullptr)
	{
		health--;
		if (health <= 0)
		{
			APawn* test = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

			int score = Cast<ARocket_gamePawn>(test)->GetScoreInt();
			score++;
			Cast<ARocket_gamePawn>(test)->SetScore(score);

			Destroy();
		}
	}

	if (Cast<ARocket>(OtherActor) != nullptr)
	{
		APawn* test = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		int score = Cast<ARocket_gamePawn>(test)->GetScoreInt();
		score++;
		Cast<ARocket_gamePawn>(test)->SetScore(score);

		Destroy();
	}

	if (Cast<APrateci_zid>(OtherActor) != nullptr)
	{
		Destroy();
	}
}
