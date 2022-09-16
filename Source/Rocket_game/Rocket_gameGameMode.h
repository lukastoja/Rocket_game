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

	int tunelBR;


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
		FTransform TunelSpawnPoint;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		FTransform SpawnPoint;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		FTransform TurretSpawnPoint;

	UFUNCTION(BlueprintCallable)
		void CreatInitialTunelTiles();

	UFUNCTION(BlueprintCallable)
		void AddTunelTile();

	void Spawn(int vjerojatnost, int i);
	void Spawn1(int vjerojatnost);
	void Spawn2(int vjerojatnost);
	void Spawn3(int vjerojatnost);
	void Spawn_loc();
	void Spawn_prepreka();
	void SetMunicijaPar(int* metak, int* raketa);
	void interpolate();
	void InterpolateTurretSpawnNumber();
	void InterpolateTurretSpawn();
	void SpawnTurret();

	float start_mat[5][5] = {
		{0.8, 0.05, 0.05, 0.05, 0.05}, // Straight
		{0.25, 0.5, 0.15, 0.05, 0.05}, // Up
		{0.25, 0.15, 0.5, 0.05, 0.05}, // Down
		{0.25, 0.05, 0.05, 0.5, 0.15}, // Left
		{0.25, 0.05, 0.05, 0.15, 0.5}, // Right
	};

	float interpolated_mat[5][5] = {
		{0.8, 0.05, 0.05, 0.05, 0.05}, // Straight
		{0.25, 0.5, 0.15, 0.05, 0.05}, // Up
		{0.25, 0.15, 0.5, 0.05, 0.05}, // Down
		{0.25, 0.05, 0.05, 0.5, 0.15}, // Left
		{0.25, 0.05, 0.05, 0.15, 0.5}, // Right
	};

	float end_mat[5][5] = {
		{0.05, 0.2375, 0.2375, 0.2375, 0.2375}, // Straight
		{0.05, 0.2375, 0.2375, 0.2375, 0.2375}, // Up
		{0.05, 0.2375, 0.2375, 0.2375, 0.2375}, // Down
		{0.05, 0.2375, 0.2375, 0.2375, 0.2375}, // Left
		{0.05, 0.2375, 0.2375, 0.2375, 0.2375}, // Right
	};

	float t_turret = 0;		//za spawnanje turreta od 0 do 4
	float t_pomak = 0.1;
	int brojTurreta = 0;

	float ucestalostT = 0;	//koliko cesto ce se stvarati turret
	float u_pomak = 0.1;

	FString labels[5] = { "straight", "up", "down", "left", "right" };

	int prosliTunel;

	int rotacijaTunelaUD;
	int rotacijaTunelaLR;

protected:
	bool tunelFlag;
};