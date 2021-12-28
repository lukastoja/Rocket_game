// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rocket.generated.h"

UCLASS()
class ROCKET_GAME_API ARocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARocket();

	UPROPERTY(EditAnywhere, Category = "Material")
	class UMaterial* MaterialRocket;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* RocketMainMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* RocketDownStab1Mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* RocketDownStab2Mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* RocketDownStab3Mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* RocketDownStab31Mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* RocketUpStab1Mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* RocketUpStab2Mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* RocketUpStab3Mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* RocketUpStab4Mesh;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	float t_init;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	float t_rest;

	UPROPERTY(EditAnywhere, Category = "Components")
	float t_speedup;

	UPROPERTY(EditAnywhere, Category = "Components")
	float t_hit;

	UPROPERTY(EditAnywhere, Category = "Components")
	float elapsed_time;

	UPROPERTY(EditAnywhere, Category = "Components")
	float elapsed_time_boundingBox;

	UPROPERTY(EditAnywhere, Category = "Components")
	float previous_elapsed_time;

	UPROPERTY(EditAnywhere, Category = "Components")
	float resting_distance;

	UPROPERTY(EditAnywhere, Category = "Components")
	FVector player_down_vec;

	UPROPERTY(EditAnywhere, Category = "Components")
	float velocity;

	UPROPERTY(EditAnywhere, Category = "Components")
	float init_player_velocity;

	UPROPERTY(EditAnywhere, Category = "Components")
	float max_velocity;

	UPROPERTY(EditAnywhere, Category = "Components")
	float player_acceleration;

	UPROPERTY(EditAnywhere, Category = "Components")
	FVector initialForwardVector;

	UPROPERTY(EditAnywhere, Category = "Components")
	FVector targetPos;

	UPROPERTY(EditAnywhere, Category = "Components")
	FVector boundingBoxEntrancerPoint;

	UPROPERTY(EditAnywhere, Category = "Components")
	bool targetSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ThrowPosition")
	UParticleSystemComponent* RocketSmoke;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float EaseInOutQuad(float t);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBulletHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

};
