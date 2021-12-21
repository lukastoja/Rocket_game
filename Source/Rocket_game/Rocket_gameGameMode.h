// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Rocket_gameGameMode.generated.h"

UCLASS(MinimalAPI)
class ARocket_gameGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override; //Override beginplay from the base class

public:
	ARocket_gameGameMode();

	void SetScore(int score);
	int GetScore();


	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<class ATunel> TunelTileClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<class ATunelDesno> TunelTileClassDesno;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<class ATunelLijevo> TunelTileClassLijevo;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<class ATunelGore> TunelTileClassGore;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<class ATunelDole> TunelTileClassDole;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<class APortal> PortalClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<class AMunicija> MunicijaClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<class APrepreka_zid> ZidClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<class ATurret> TurretClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	int32 NumInitialTunelTiles = 50;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform NextSpawnPoint;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform SpawnPoint;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform TurretSpawnPoint;

	UFUNCTION(BlueprintCallable)
	void CreatInitialTunelTiles();

	UFUNCTION(BlueprintCallable)
	void AddTunelTile();

	void Spawn1(int vjerojatnost);
	void Spawn2(int vjerojatnost);
	void Spawn3(int vjerojatnost);
	void Spawn_loc();
	void Spawn_prepreka();
	void SetMunicijaPar(int* metak, int* raketa);

	void SpawnTurret();

protected:
	bool tunelFlag;
};