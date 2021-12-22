// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Rocket_gameGameMode.h"
#include "Rocket_gamePawn.h"
#include "UObject/ConstructorHelpers.h"
#include "RocketPlayerController.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "Components/SceneComponent.h"
#include "RocketGameState.h"
#include "Tunel.h"
#include "TunelDesno.h"
#include "TunelLijevo.h"
#include "TunelDole.h"
#include "TunelGore.h"
#include "Portal.h"
#include "Municija.h"
#include "Prepreka_zid.h"
#include "Turret.h"

ARocket_gameGameMode::ARocket_gameGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = ARocket_gamePawn::StaticClass();

	PlayerControllerClass = ARocketPlayerController::StaticClass();

}

void ARocket_gameGameMode::SetScore(int score1)
{
	ARocketGameState* GS = Cast<ARocketGameState>(GameState);
	GS->score = score1;
}

int ARocket_gameGameMode::GetScore()
{
	ARocketGameState* GS = Cast<ARocketGameState>(GameState);
	if (GS != nullptr)
	{
		return GS->score;
	}
	return 100;
}

void ARocket_gameGameMode::Spawn_loc()
{
	//napraviti da se može u ciejlom krugu postavljati portal
	float r = FMath::RandRange(0, 1310);
	float x = SpawnPoint.GetLocation().X;
	float y = FMath::RandRange(-r, r);
	float z = 0;
	int vjv = FMath::RandRange(0, 100);
	
	if (vjv < 50)
	{
		z = FMath::Sqrt(FMath::Pow(r, 2) - FMath::Pow(y, 2));
	} else {
		z = -FMath::Sqrt(FMath::Pow(r, 2) - FMath::Pow(y, 2));
	}

	FTransform PortalSpawnTransform;
	PortalSpawnTransform.SetLocation(FVector(x,y,z));

	SpawnPoint = PortalSpawnTransform;
}

void ARocket_gameGameMode::Spawn_prepreka()
{
	APrepreka_zid* zid = GetWorld()->SpawnActor<APrepreka_zid>(ZidClass, SpawnPoint);
	int health = FMath::RandRange(1, 10);
	zid->SetHealth(health);

	int x1, y1, z1;
	x1 = FMath::RandRange(-10, 10);
	y1 = FMath::RandRange(-30, 30);
	z1 = FMath::RandRange(-30, 30);
	zid->SetMovement(x1, y1, z1);

	x1 = FMath::RandRange(1, 10);
	y1 = FMath::RandRange(1, 20);
	z1 = FMath::RandRange(1, 20);

	zid->SetActorScale3D(FVector(x1, y1, z1));
}

void ARocket_gameGameMode::SetMunicijaPar(int* metak, int* raketa)
{
	int m = FMath::RandRange(0, 10);

	if (m < 3)
	{
		*metak = 10;
		*raketa = 0;
	}
	else if (m < 6)
	{
		*metak = 5;
		*raketa = 5;
	}
	else
	{
		*raketa = 10;
		*metak = 0;
	}
}

void ARocket_gameGameMode::Spawn1(int vjerojatnost)
{
	if (vjerojatnost < 25)
	{
		Spawn_loc();
		APortal* portal = GetWorld()->SpawnActor<APortal>(PortalClass, SpawnPoint);
	}
	else if (vjerojatnost < 50)
	{
		Spawn_loc();
		int raketa = 0;
		int metak = 0;
		SetMunicijaPar(&metak, &raketa);
		AMunicija* municija = GetWorld()->SpawnActor<AMunicija>(MunicijaClass, SpawnPoint);
		municija->SetMunicija(metak, raketa);
	}
	else if (vjerojatnost < 90)
	{
		Spawn_prepreka();
	}
}

void ARocket_gameGameMode::Spawn2(int vjerojatnost)
{
	if (vjerojatnost < 40)
	{
		Spawn_loc();
		APortal* portal = GetWorld()->SpawnActor<APortal>(PortalClass, SpawnPoint);
	}
	else if (vjerojatnost < 65)
	{
		Spawn_loc();
		int raketa = 0;
		int metak = 0;
		SetMunicijaPar(&metak, &raketa);
		AMunicija* municija = GetWorld()->SpawnActor<AMunicija>(MunicijaClass, SpawnPoint);
		municija->SetMunicija(metak, raketa);
	}
	else if (vjerojatnost < 90)
	{
		Spawn_prepreka();
	}
}

void ARocket_gameGameMode::Spawn3(int vjerojatnost)
{
	if(vjerojatnost < 25)
	{
		Spawn_loc();
		APortal* portal = GetWorld()->SpawnActor<APortal>(PortalClass, SpawnPoint);
	}
	else if (vjerojatnost < 65)
	{
		Spawn_loc();
		int raketa = 0;
		int metak = 0;
		SetMunicijaPar(&metak, &raketa);
		AMunicija* municija = GetWorld()->SpawnActor<AMunicija>(MunicijaClass, SpawnPoint);
		municija->SetMunicija(metak, raketa);
	}
	else if (vjerojatnost < 90)
	{
		Spawn_prepreka();
	}
}

void ARocket_gameGameMode::SpawnTurret()
{
	ATurret* turret = GetWorld()->SpawnActor<ATurret>(TurretClass, TurretSpawnPoint);
}

void ARocket_gameGameMode::CreatInitialTunelTiles()
{
	for (int i = 0; i < NumInitialTunelTiles; i++)
	{
		AddTunelTile();
	}
}

void ARocket_gameGameMode::AddTunelTile()
{
	UWorld* World = GetWorld();

	if (World)
	{
		int m = FMath::RandRange(1, 10);
		if (m > 8)
		{
			ATunel* tunel = GetWorld()->SpawnActor<ATunel>(TunelTileClass, NextSpawnPoint);
			if (tunel)
			{
				NextSpawnPoint = tunel->GetAttachTransform();
			}

			//odlucivanje sto ce se spawnat na koji spawn point
			if (tunelFlag)
			{
				int spawnpoint1 = FMath::RandRange(0, 100);
				int spawnpoint2 = FMath::RandRange(0, 100);
				int spawnpoint3 = FMath::RandRange(0, 100);

				SpawnPoint = tunel->GetSpawnPoint1();
				Spawn1(spawnpoint1);

				SpawnPoint = tunel->GetSpawnPoint2();
				Spawn2(spawnpoint2);

				SpawnPoint = tunel->GetSpawnPoint3();
				Spawn3(spawnpoint3);

			}
			tunelFlag = true;

			TurretSpawnPoint = tunel->GetTurretSpawnPoint1();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint2();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint3();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint4();
			SpawnTurret();
		}
		else if (m > 6){
			ATunelDesno* tunel = GetWorld()->SpawnActor<ATunelDesno>(TunelTileClassDesno, NextSpawnPoint);
			if (tunel)
			{
				NextSpawnPoint = tunel->GetAttachTransform();
			}

			//odlucivanje sto ce se spawnat na koji spawn point
			/*if (tunelFlag)
			{
				int spawnpoint1 = FMath::RandRange(0, 100);
				int spawnpoint2 = FMath::RandRange(0, 100);
				int spawnpoint3 = FMath::RandRange(0, 100);

				SpawnPoint = tunel->GetSpawnPoint1();
				Spawn1(spawnpoint1);

				SpawnPoint = tunel->GetSpawnPoint2();
				Spawn2(spawnpoint2);

				SpawnPoint = tunel->GetSpawnPoint3();
				Spawn3(spawnpoint3);
			}
			tunelFlag = true;*/

			TurretSpawnPoint = tunel->GetTurretSpawnPoint1();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint2();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint3();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint4();
			SpawnTurret();
		}
		else if (m > 4) {
			ATunelLijevo* tunel = GetWorld()->SpawnActor<ATunelLijevo>(TunelTileClassLijevo, NextSpawnPoint);
			if (tunel)
			{
				NextSpawnPoint = tunel->GetAttachTransform();
			}

			//odlucivanje sto ce se spawnat na koji spawn point
			/*if (tunelFlag)
			{
				int spawnpoint1 = FMath::RandRange(0, 100);
				int spawnpoint2 = FMath::RandRange(0, 100);
				int spawnpoint3 = FMath::RandRange(0, 100);

				SpawnPoint = tunel->GetSpawnPoint1();
				Spawn1(spawnpoint1);

				SpawnPoint = tunel->GetSpawnPoint2();
				Spawn2(spawnpoint2);

				SpawnPoint = tunel->GetSpawnPoint3();
				Spawn3(spawnpoint3);
			}
			tunelFlag = true;*/

			TurretSpawnPoint = tunel->GetTurretSpawnPoint1();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint2();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint3();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint4();
			SpawnTurret();
		}
		else if (m > 2) {
			ATunelGore* tunel = GetWorld()->SpawnActor<ATunelGore>(TunelTileClassGore, NextSpawnPoint);
			if (tunel)
			{
				NextSpawnPoint = tunel->GetAttachTransform();
			}

			//odlucivanje sto ce se spawnat na koji spawn point
			/*if (tunelFlag)
			{
				int spawnpoint1 = FMath::RandRange(0, 100);
				int spawnpoint2 = FMath::RandRange(0, 100);
				int spawnpoint3 = FMath::RandRange(0, 100);

				SpawnPoint = tunel->GetSpawnPoint1();
				Spawn1(spawnpoint1);

				SpawnPoint = tunel->GetSpawnPoint2();
				Spawn2(spawnpoint2);

				SpawnPoint = tunel->GetSpawnPoint3();
				Spawn3(spawnpoint3);
			}
			tunelFlag = true;*/

			TurretSpawnPoint = tunel->GetTurretSpawnPoint1();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint2();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint3();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint4();
			SpawnTurret();
		}
		else {
			ATunelDole* tunel = GetWorld()->SpawnActor<ATunelDole>(TunelTileClassDole, NextSpawnPoint);
			if (tunel)
			{
				NextSpawnPoint = tunel->GetAttachTransform();
			}

			//odlucivanje sto ce se spawnat na koji spawn point
			/*if (tunelFlag)
			{
				int spawnpoint1 = FMath::RandRange(0, 100);
				int spawnpoint2 = FMath::RandRange(0, 100);
				int spawnpoint3 = FMath::RandRange(0, 100);

				SpawnPoint = tunel->GetSpawnPoint1();
				Spawn1(spawnpoint1);

				SpawnPoint = tunel->GetSpawnPoint2();
				Spawn2(spawnpoint2);

				SpawnPoint = tunel->GetSpawnPoint3();
				Spawn3(spawnpoint3);
			}
			tunelFlag = true;*/

			TurretSpawnPoint = tunel->GetTurretSpawnPoint1();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint2();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint3();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint4();
			SpawnTurret();
		}
	}
}


void ARocket_gameGameMode::BeginPlay()
{
	Super::BeginPlay();
	tunelFlag = false;

	UWorld* TheWorld = GetWorld();
	FString CurrentLevel = TheWorld->GetMapName();
	CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (CurrentLevel == "MainMenuMap" || CurrentLevel == "EndLevel")
	{

		if (PC)
		{
			PC->bShowMouseCursor = true;
			PC->bEnableClickEvents = true;
			PC->bEnableMouseOverEvents = true;
		}
	}
	else {
		if (PC)
		{
			PC->bShowMouseCursor = false;
			PC->bEnableClickEvents = false;
			PC->bEnableMouseOverEvents = false;
		}
		CreatInitialTunelTiles();
	}
}
