// Fill out your copyright notice in the Description page of Project Settings.


#include "Rocket.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "Components/StaticMeshComponent.h"
#include "Turret.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ARocket::ARocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RocketMainMesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketMainMesh");
	SetRootComponent(RocketMainMesh);

	RocketDownStab1Mesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketDownStab1Mesh");
	RocketDownStab1Mesh->SetupAttachment(RootComponent);

	RocketDownStab2Mesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketDownStab2Mesh");
	RocketDownStab2Mesh->SetupAttachment(RootComponent);

	RocketDownStab3Mesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketDownStab3Mesh");
	RocketDownStab3Mesh->SetupAttachment(RootComponent);

	RocketDownStab31Mesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketDownStab31Mesh");
	RocketDownStab31Mesh->SetupAttachment(RootComponent);

	RocketUpStab1Mesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketUpStab1Mesh");
	RocketUpStab1Mesh->SetupAttachment(RootComponent);

	RocketUpStab2Mesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketUpStab2Mesh");
	RocketUpStab2Mesh->SetupAttachment(RootComponent);

	RocketUpStab3Mesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketUpStab3Mesh");
	RocketUpStab3Mesh->SetupAttachment(RootComponent);

	RocketUpStab4Mesh = CreateDefaultSubobject<UStaticMeshComponent>("RocketUpStab4Mesh");
	RocketUpStab4Mesh->SetupAttachment(RootComponent);

	targetSet = false;

	OnActorHit.AddDynamic(this, &ARocket::OnBulletHit);
}

float ARocket::EaseInOutQuad(float t)
{
	if (t < 0.5)
	{
		return 2 * t * t;
	}
	else {
		t = t - 0.5;
		return 2 * t * (1 - t) + 0.5;
	}

}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();
	
	t_init = 0.5;
	t_rest = 0.8;
	t_speedup = 0.8;
	t_hit = 0.5;
	elapsed_time = 0;
	resting_distance = 15;
	previous_elapsed_time = 0;
	elapsed_time_boundingBox = 0;
	initialForwardVector = GetActorForwardVector();
}

// Called every frame
void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	previous_elapsed_time = elapsed_time;
	elapsed_time = elapsed_time + DeltaTime;

	if (targetSet)
	{
		elapsed_time_boundingBox += DeltaTime;
		UE_LOG(LogTemp, Warning, TEXT("postavio sam target"));
		if (elapsed_time_boundingBox > t_hit)
		{
			Destroy();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Usao sam u box"));
			FVector f_prev = GetActorLocation();
			FVector diff = targetPos - boundingBoxEntrancerPoint;

			float cosAlpha = (FVector::DotProduct(initialForwardVector, diff) / (initialForwardVector.Size() * diff.Size()));

			float d = cosAlpha * diff.Size();

			FVector C = boundingBoxEntrancerPoint + initialForwardVector * d;
			float t = elapsed_time_boundingBox / t_hit;

			UE_LOG(LogTemp, Warning, TEXT("t: %f, d: %f, cosAlpha: %f"), t, d, cosAlpha);


			FVector f1 = boundingBoxEntrancerPoint * (1 - t) + C * t;
			FVector f2 = C * (1 - t) + targetPos * t;
			FVector f = f1 * (1 - t) + f2 * t;
			SetActorLocation(f);

			FVector orientation = f - f_prev;

			SetActorRotation(orientation.Rotation());
		}
	}
	else
	{
		if (elapsed_time < t_init)
		{
			float delta = EaseInOutQuad(elapsed_time / t_init) - EaseInOutQuad(previous_elapsed_time / t_init);
			float delta_movement = delta * resting_distance;
			FVector Location = GetActorLocation() + player_down_vec * delta_movement + GetActorForwardVector() * delta * (-400);
			SetActorLocation(Location);

			Location = GetActorLocation();
			Location += GetActorForwardVector() * velocity * DeltaTime;
			SetActorLocation(Location);
		}
		else if (elapsed_time < t_init + t_rest)
		{
			//Pomaknuti raketu u smjeru njenog forward vectora za velocity * delta_time
			FVector Location = GetActorLocation();
			Location += GetActorForwardVector() * velocity * DeltaTime;
			SetActorLocation(Location);

		}
		else if (elapsed_time < t_init + t_rest + t_speedup)
		{
			//Pomaknuti raketu u smjeru njenog forward vektora za velocity * delta_time
			float velocity1 = velocity + EaseInOutQuad((elapsed_time - t_init - t_rest) / t_speedup) * max_velocity;

			FVector Location = GetActorLocation();
			Location += GetActorForwardVector() * velocity1 * DeltaTime;
			SetActorLocation(Location);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("nije postavljen target"));
			float velocity1 = velocity + max_velocity;

			FVector Location = GetActorLocation();
			Location += GetActorForwardVector() * velocity1 * DeltaTime;
			SetActorLocation(Location);
		}
	}

	float newVelocity = velocity + (DeltaTime * player_acceleration);
	velocity = FMath::Clamp(newVelocity, 500.f, 10000.f);
}


void ARocket::OnBulletHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<ATurret>(OtherActor) != nullptr)
	{
		Cast<ATurret>(OtherActor)->Destroy();
	}
}

