// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class ROCKET_GAME_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh1;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh2;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh3;

	UPROPERTY(EditAnywhere, Category = "Constants")
	float sensingRange;

	bool FindBestTarget();
	void SetTurretRotation(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Components")
		FRotator okretanje;

	UPROPERTY(EditAnywhere, Category = "Components")
		float rotacijax;

	UPROPERTY(EditAnywhere, Category = "Components")
		float rotacijay;

	UPROPERTY(EditAnywhere, Category = "Components")
		float rotacijaz;

	UPROPERTY(EditAnywhere, Category = "Components")
		float kolikox;

	UPROPERTY(EditAnywhere, Category = "Components")
		float kolikoy;

	UPROPERTY(EditAnywhere, Category = "Components")
		float kolikoz;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USphereComponent* MySphereComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USphereComponent* MySphereComponentSensing;

	int radius;

	float currentDistance;

	UPROPERTY(EditAnywhere, Category = "Components")
	float TraceDistance;

private:
	AActor* currentTarget;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/*UFUNCTION()
	void OnOverlapBeginSensing(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	*/
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
