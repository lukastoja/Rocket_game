// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TunelGlavni.generated.h"

UCLASS()
class ROCKET_GAME_API ATunelGlavni : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATunelGlavni();

	UFUNCTION(BlueprintPure, Category = "Component")
		FTransform GetAttachTransform();

	UFUNCTION(BlueprintPure, Category = "Component")
		FTransform GetSpawnPoint(int i);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Material")
		class UMaterial* MaterialTunel;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UStaticMeshComponent* TunelMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
		class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UArrowComponent* AttachPoint;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, Category = "Components")
		class ARocket_gameGameMode* RocketGameMode;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void DestroyTunelTile();

	UPROPERTY(EditAnywhere, Category = "Components")
		FTimerHandle DestroyHandle;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UArrowComponent* SpawnPoint1;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UArrowComponent* SpawnPoint2;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UArrowComponent* SpawnPoint3;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UArrowComponent* TurretSpawnPoint1;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UArrowComponent* TurretSpawnPoint2;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UArrowComponent* TurretSpawnPoint3;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UArrowComponent* TurretSpawnPoint4;

	UFUNCTION(BlueprintPure, Category = "Component")	//dohvati bilo koji spawn ovisno o broju 1, 2, 3, 4 
		FTransform GetTurretSpawnPoint(int i);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
