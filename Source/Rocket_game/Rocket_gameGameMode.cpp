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
#include "GenericPlatform/GenericPlatformMath.h"

ARocket_gameGameMode::ARocket_gameGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = ARocket_gamePawn::StaticClass();

	PlayerControllerClass = ARocketPlayerController::StaticClass();
	SpawnPoint = FTransform(FVector(1, 1, 1));
	prosliTunel = 0;
	rotacijaTunela = 0;
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

void ARocket_gameGameMode::interpolate()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			float t = tunelBR / 10.f;
			FGenericPlatformMath::Min(t, 1.f);
			FGenericPlatformMath::Max(0.f, t);
			interpolated_mat[i][j] = start_mat[i][j] * (1 - t) + end_mat[i][j] * t;
		}
	}

}

void ARocket_gameGameMode::Spawn_loc()
{
	float r = FMath::RandRange(0, 500);
	float x = 0;
	float y = FMath::RandRange(-r, r);
	float z = 0;

	int vjv = FMath::RandRange(0, 100);
	
	z = FMath::Sqrt(FMath::Pow(r, 2) - FMath::Pow(y, 2));

	if (vjv < 50)
	{
		z = -z;
	}

	FTransform PortalSpawnTransform;
	PortalSpawnTransform.SetLocation(FVector(x,y,z) + SpawnPoint.GetLocation());
	PortalSpawnTransform.SetRotation(SpawnPoint.GetRotation());

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
		portal->TunelLocation = TunelSpawnPoint.GetLocation();
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
		Spawn_loc();
		Spawn_prepreka();
	}
}

void ARocket_gameGameMode::Spawn2(int vjerojatnost)
{
	if (vjerojatnost < 40)
	{
		Spawn_loc();
		APortal* portal = GetWorld()->SpawnActor<APortal>(PortalClass, SpawnPoint);
		portal->TunelLocation = TunelSpawnPoint.GetLocation();
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

void ARocket_gameGameMode::Spawn3(int vjerojatnost)
{
	if (vjerojatnost < 25)
	{
		Spawn_loc();
		APortal* portal = GetWorld()->SpawnActor<APortal>(PortalClass, SpawnPoint);
		portal->TunelLocation = TunelSpawnPoint.GetLocation();
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
		int odabir = 0;

		float choice = FMath::RandRange(0, 100) / 100.f;
		if (choice <= interpolated_mat[prosliTunel][0])
		{
			odabir = 0;
		}
		else if (choice <= interpolated_mat[prosliTunel][1] + interpolated_mat[prosliTunel][0])
		{
			odabir = 1;
		}
		else if (choice <= interpolated_mat[prosliTunel][2] + interpolated_mat[prosliTunel][1] + interpolated_mat[prosliTunel][0])
		{
			odabir = 2;
		}
		else if (choice <= interpolated_mat[prosliTunel][3] + interpolated_mat[prosliTunel][2] + interpolated_mat[prosliTunel][1] + interpolated_mat[prosliTunel][0])
		{
			odabir = 3;
			rotacijaTunela = rotacijaTunela + 20;
			if (rotacijaTunela >= 150)
			{
				odabir = 4;
				rotacijaTunela = rotacijaTunela - 40;
			}
		}
		else
		{
			odabir = 4;
			rotacijaTunela = rotacijaTunela - 20;
			if (rotacijaTunela <= -150)
			{
				odabir = 3;
				rotacijaTunela = rotacijaTunela + 40;
			}
		}

		if (odabir == 0)
		{
			ATunel* tunel = GetWorld()->SpawnActor<ATunel>(TunelTileClass, NextSpawnPoint);
			if (tunel)
			{
				TunelSpawnPoint = tunel->GetActorTransform();;
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
			prosliTunel = 0;

			/*TurretSpawnPoint = tunel->GetTurretSpawnPoint1();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint2();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint3();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint4();
			SpawnTurret();*/
		}
		else if (odabir == 1) {
			ATunelDesno* tunelD = GetWorld()->SpawnActor<ATunelDesno>(TunelTileClassDesno, NextSpawnPoint);
			if (tunelD)
			{
				TunelSpawnPoint = tunelD->GetActorTransform();;
				NextSpawnPoint = tunelD->GetAttachTransform();
			}

			//odlucivanje sto ce se spawnat na koji spawn point
			if (tunelFlag)
			{
				int spawnpoint1 = FMath::RandRange(0, 100);
				int spawnpoint2 = FMath::RandRange(0, 100);
				int spawnpoint3 = FMath::RandRange(0, 100);

				SpawnPoint = tunelD->GetSpawnPoint1();
				Spawn1(spawnpoint1);

				SpawnPoint = tunelD->GetSpawnPoint2();
				Spawn2(spawnpoint2);

				SpawnPoint = tunelD->GetSpawnPoint3();
				Spawn3(spawnpoint3);
			}
			tunelFlag = true;
			prosliTunel = 1;

			/*TurretSpawnPoint = tunel->GetTurretSpawnPoint1();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint2();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint3();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint4();
			SpawnTurret();*/
		}
		else if (odabir == 2) {
			ATunelLijevo* tunelL = GetWorld()->SpawnActor<ATunelLijevo>(TunelTileClassLijevo, NextSpawnPoint);
			if (tunelL)
			{
				TunelSpawnPoint = tunelL->GetActorTransform();
				NextSpawnPoint = tunelL->GetAttachTransform();
			}

			//odlucivanje sto ce se spawnat na koji spawn point
			if (tunelFlag)
			{
				int spawnpoint1 = FMath::RandRange(0, 100);
				int spawnpoint2 = FMath::RandRange(0, 100);
				int spawnpoint3 = FMath::RandRange(0, 100);

				SpawnPoint = tunelL->GetSpawnPoint1();
				Spawn1(spawnpoint1);

				SpawnPoint = tunelL->GetSpawnPoint2();
				Spawn2(spawnpoint2);

				SpawnPoint = tunelL->GetSpawnPoint3();
				Spawn3(spawnpoint3);
			}
			tunelFlag = true;
			prosliTunel = 2;
			
			/*TurretSpawnPoint = tunel->GetTurretSpawnPoint1();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint2();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint3();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint4();
			SpawnTurret();*/
		}
		else if (odabir == 3) {
			ATunelGore* tunelG = GetWorld()->SpawnActor<ATunelGore>(TunelTileClassGore, NextSpawnPoint);
			if (tunelG)
			{
				TunelSpawnPoint = tunelG->GetActorTransform();;
				NextSpawnPoint = tunelG->GetAttachTransform();
			}

			//odlucivanje sto ce se spawnat na koji spawn point
			if (tunelFlag)
			{
				int spawnpoint1 = FMath::RandRange(0, 100);
				int spawnpoint2 = FMath::RandRange(0, 100);
				int spawnpoint3 = FMath::RandRange(0, 100);

				SpawnPoint = tunelG->GetSpawnPoint1();
				Spawn1(spawnpoint1);

				SpawnPoint = tunelG->GetSpawnPoint2();
				Spawn2(spawnpoint2);

				SpawnPoint = tunelG->GetSpawnPoint3();
				Spawn3(spawnpoint3);
			}
			tunelFlag = true;
			prosliTunel = 3;

			/*TurretSpawnPoint = tunel->GetTurretSpawnPoint1();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint2();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint3();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint4();
			SpawnTurret();*/
		}
		else {
			ATunelDole* tunelDL = GetWorld()->SpawnActor<ATunelDole>(TunelTileClassDole, NextSpawnPoint);
			if (tunelDL)
			{
				TunelSpawnPoint = tunelDL->GetActorTransform();
				NextSpawnPoint = tunelDL->GetAttachTransform();
			}

			//odlucivanje sto ce se spawnat na koji spawn point
			if (tunelFlag)
			{
				int spawnpoint1 = FMath::RandRange(0, 100);
				int spawnpoint2 = FMath::RandRange(0, 100);
				int spawnpoint3 = FMath::RandRange(0, 100);

				SpawnPoint = tunelDL->GetSpawnPoint1();
				Spawn1(spawnpoint1);

				SpawnPoint = tunelDL->GetSpawnPoint2();
				Spawn2(spawnpoint2);

				SpawnPoint = tunelDL->GetSpawnPoint3();
				Spawn3(spawnpoint3);
			}
			tunelFlag = true;
			prosliTunel = 4;

			/*TurretSpawnPoint = tunel->GetTurretSpawnPoint1();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint2();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint3();
			SpawnTurret();
			TurretSpawnPoint = tunel->GetTurretSpawnPoint4();
			SpawnTurret();*/
		}
	}

	tunelBR++;
	interpolate();
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
			PC->bShowMouseCursor = true;
			PC->bEnableClickEvents = true;
			PC->bEnableMouseOverEvents = true;
		}
		CreatInitialTunelTiles();
	}
}
