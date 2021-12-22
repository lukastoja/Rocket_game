// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Engine.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Rocket_gamePawn.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");
	SetRootComponent(BulletMesh);

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BulletMovement");
	BulletMovement->InitialSpeed = 3500.f;
	BulletMovement->MaxSpeed = 3500.f;
	BulletMovement->ProjectileGravityScale = 0;

	MaterialBullet = CreateDefaultSubobject<UMaterial>("MaterialBullet");

	OnActorHit.AddDynamic(this, &ABullet::OnBulletHit);
	turretFlag = false;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	AActor* mojLik = GetOwner();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnBulletHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{

	if (Cast<ARocket_gamePawn>(OtherActor) != nullptr)
	{
		Destroy();
		if (turretFlag)
		{
			Cast<ARocket_gamePawn>(OtherActor)->lowerHP();
		}
		else
		{
			Cast<ARocket_gamePawn>(OtherActor)->UpdateBr_metaka(1, 0);
		}
		return;
	}
	Destroy();
}
