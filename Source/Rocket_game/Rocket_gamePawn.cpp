// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Rocket_gamePawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Blueprint/UserWidget.h"
#include "Portal.h"
#include "Components/SceneComponent.h"
#include "Bullet.h"
#include "Engine.h"
#include "Rocket_gameGameMode.h"
#include "RocketGameInstance.h"
#include "TimerManager.h"
#include "Components/PointLightComponent.h"
#include "Rocket.h"
#include "MySaveGame.h"

ARocket_gamePawn::ARocket_gamePawn()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Flying/Meshes/SvemirskiBrodFinal"))
		{
		}
	};

	static FConstructorStatics ConstructorStatics;


	// Create static mesh component
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh0"));
	PlaneMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());	// Set static mesh
	SetRootComponent(PlaneMesh);


	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);	// Attach SpringArm to RootComponent
	SpringArm->TargetArmLength = 160.0f; // The camera follows at this distance behind the character	
	SpringArm->SocketOffset = FVector(0.f,0.f,150.f);
	SpringArm->bEnableCameraLag = false;	// Do not allow camera to lag
	SpringArm->CameraLagSpeed = 15.f;

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);	// Attach the camera
	Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->SetupAttachment(RootComponent);

	Lights = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightComponent"));
	Lights->SetupAttachment(RootComponent);

	// Set handling parameters
	Acceleration = 100.f;
	TurnSpeed = 50.f;
	MaxSpeed = 10000.f;
	MinSpeed = 500.f;
	CurrentForwardSpeed = 500.f;
	score = 0;
	br_metaka = 10;
	br_raketa = 10;
	max_metaka = 30;
	max_raketa = 30;
	Lokacija_Metka = 100.f;
	health = 10;

	zapocni_load = false;

	//kreiranje widgeta
	static ConstructorHelpers::FClassFinder<UUserWidget> ScoreHud(TEXT("/Game/Blueprints/widgets/ScoreWidget"));
	MainHUDClass = ScoreHud.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuHud(TEXT("/Game/Blueprints/widgets/MainMenuWidget"));
	MainMenuHUDClass = MainMenuHud.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> HelpHUD(TEXT("/Game/Blueprints/widgets/HelpWidget"));
	HelpHUDClass = HelpHUD.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> PauseHUD(TEXT("/Game/Blueprints/widgets/PauseWidget"));
	PauseHUDClass = PauseHUD.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> EndHUD(TEXT("/Game/Blueprints/widgets/EndWidget"));
	EndHUDClass = EndHUD.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> LevelHUD(TEXT("/Game/Blueprints/widgets/LevelWidget"));
	LevelHUDClass = LevelHUD.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ScoreBoardHUD(TEXT("/Game/Blueprints/widgets/ScoreBoardWidget"));
	ScoreboardHUDClass = ScoreBoardHUD.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ShopHUD(TEXT("/Game/Blueprints/widgets/ShopWidget"));
	ShopHUDClass = ShopHUD.Class;


	//Box->OnComponentBeginOverlap.AddDynamic(this, &ARocket_gamePawn::OnOverlapBegin);
	flag = false;

	loadingSequanceTimer = 0.f;
	savingSequanceTimer = 0.f;
	hasCompletedLoadGame = false;
	isAssemblingSaveGameData = false;
	canSaveGame = false;
}

int ARocket_gamePawn::GetBr_metaka()
{
	return br_metaka;
}

int ARocket_gamePawn::GetBr_raketa()
{
	return br_raketa;
}

void ARocket_gamePawn::Destroy_Pawn()
{
	URocketGameInstance* GI = Cast<URocketGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GI->score = score;
	GI->scoreboard[10] = score;
	GI->sortScoreboard();
	UE_LOG(LogTemp, Warning, TEXT("coins: %d"), GI->coins);
	GI->setCoins();
	UE_LOG(LogTemp, Warning, TEXT("coins: %d"), GI->coins);

	//test coins
	GI->setCoinsTest();
	UGameplayStatics::OpenLevel(this, "EndLevel");
}

void ARocket_gamePawn::Start_Game()
{
	URocketGameInstance* GI = Cast<URocketGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GI->score = 0;
	UE_LOG(LogTemp, Warning, TEXT("coins: %d"), GI->coins);
	UGameplayStatics::OpenLevel(this, "Level1");
}

void ARocket_gamePawn::Help_menu()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HelpHUDClass);
		CurrentWidget->AddToViewport();
	}
}

void ARocket_gamePawn::Pause_Game()
{
	CurrentWidget->RemoveFromViewport();
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PauseHUDClass);

	if (CurrentWidget != nullptr)
	{
		CurrentWidget->AddToViewport();
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
}

void ARocket_gamePawn::UnPause_Game()
{
	CurrentWidget->RemoveFromViewport();
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MainHUDClass);

	if (CurrentWidget != nullptr)
	{
		CurrentWidget->AddToViewport();
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = false;
	}
}

void ARocket_gamePawn::Quit_game()
{
	UWorld* TheWorld = GetWorld();
	FString CurrentLevel = TheWorld->GetMapName();
	CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	if (CurrentLevel == "MainMenuMap" || CurrentLevel == "EndLevel")
	{
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	}
	if (CurrentLevel == "Level1" || CurrentLevel == "FlyingExampleMap")
	{
		UGameplayStatics::OpenLevel(this, "MainMenuMap");
	}
}

void ARocket_gamePawn::Open_levels()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), LevelHUDClass);
		CurrentWidget->AddToViewport();
		flag = true;
	}
}

void ARocket_gamePawn::Open_scoreboard()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), ScoreboardHUDClass);
		CurrentWidget->AddToViewport();
	}
}

void ARocket_gamePawn::Open_level_test()
{
	URocketGameInstance* GI = Cast<URocketGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GI->score = 0;
	UGameplayStatics::OpenLevel(this, "FlyingExampleMap");
}

void ARocket_gamePawn::Open_level_mainMenu()
{
	URocketGameInstance* GI = Cast<URocketGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GI->score = 0;
	UGameplayStatics::OpenLevel(this, "MainMenuMap");
}

void ARocket_gamePawn::Open_shop()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), ShopHUDClass);
		CurrentWidget->AddToViewport();
	}
}

void ARocket_gamePawn::lowerHP()
{
	health--;
	if (health <= 0)
	{
		Destroy_Pawn();
	}
}

float ARocket_gamePawn::GetHPPercent()
{
	return health / 10;
}

void ARocket_gamePawn::Back()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();

		if (flag)
		{
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuHUDClass);
			CurrentWidget->AddToViewport();
			flag = false;
		}
		else {

			UWorld* TheWorld = GetWorld();
			FString CurrentLevel = TheWorld->GetMapName();
			CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
			if (CurrentLevel == "MainMenuMap")
			{
				CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuHUDClass);
				CurrentWidget->AddToViewport();
			}
			if (CurrentLevel == "Level1")
			{
				CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PauseHUDClass);
				CurrentWidget->AddToViewport();
			}
			if (CurrentLevel == "FlyingExampleMap")
			{
				CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PauseHUDClass);
				CurrentWidget->AddToViewport();
			}
		}
	}
}

int ARocket_gamePawn::GetMax_metaka()
{
	return max_metaka;
}

void ARocket_gamePawn::UpdateBr_metaka(int metak, int raketa)
{
	br_metaka = br_metaka + metak;
	if (br_metaka <= 0)
	{
		br_metaka = 0;
	}
	if (br_metaka >= max_metaka)
	{
		br_metaka = max_metaka;
	}

	br_raketa = br_raketa + raketa;
	if (br_raketa <= 0)
	{
		br_raketa = 0;
	}
	if (br_raketa >= max_raketa)
	{
		br_raketa = max_raketa;
	}
}

void ARocket_gamePawn::Shoot()
{

	if (br_metaka <= 0)
	{

		br_metaka = 0;
		return;
	}
	if (BulletClass)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.bNoFail = true;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = this;

		FTransform BulletSpawnTransform;
		BulletSpawnTransform.SetLocation(GetActorForwardVector() * Lokacija_Metka + GetActorLocation());
		BulletSpawnTransform.SetRotation(GetActorRotation().Quaternion());
		BulletSpawnTransform.SetScale3D(FVector(1.f));

		GetWorld()->SpawnActor<ABullet>(BulletClass, BulletSpawnTransform, SpawnParameters);
		UpdateBr_metaka(-1, 0);
	}
}

void ARocket_gamePawn::ShootRocket()
{
	if (br_raketa <= 0)
	{

		br_raketa = 0;
		return;
	}
	if (RocketClass)
	{

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.bNoFail = true;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = this;

		FTransform BulletSpawnTransform;
		BulletSpawnTransform.SetLocation(GetActorUpVector() * Lokacija_Metka * (-1) + GetActorLocation());
		BulletSpawnTransform.SetRotation(GetActorRotation().Quaternion());
		BulletSpawnTransform.SetScale3D(FVector(1.f));

		ARocket* rocket = GetWorld()->SpawnActor<ARocket>(RocketClass, BulletSpawnTransform, SpawnParameters);

		rocket->player_down_vec = GetActorUpVector() * -1;
		rocket->velocity = CurrentForwardSpeed;
		rocket->init_player_velocity = CurrentForwardSpeed;
		rocket->player_acceleration = Acceleration;
		rocket->max_velocity = 20000.f;

		UpdateBr_metaka(0, -1);
	}
}

void ARocket_gamePawn::SetLoadGame()
{
	zapocni_load = true;
}

void ARocket_gamePawn::SetSaveGame()
{
	canSaveGame = true;
}

void ARocket_gamePawn::BeginPlay()
{
	Super::BeginPlay();

	UWorld* TheWorld = GetWorld();
	FString CurrentLevel = TheWorld->GetMapName();
	CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	if (CurrentLevel == "MainMenuMap")
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuHUDClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
		SetLoadGame();
	} else if (CurrentLevel == "FlyingExampleMap" || CurrentLevel == "Level1") {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), MainHUDClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
			GetWorldTimerManager().SetTimer(PovecajHandle, this, &ARocket_gamePawn::PovecajScore, 1.f, true); //1 sec
		}
	}
	else if (CurrentLevel == "EndLevel")
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), EndHUDClass);

		if (CurrentWidget)
		{
			URocketGameInstance* GI = Cast<URocketGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			score = GI->score;
			SetSaveGame();
			CurrentWidget->AddToViewport();
		}
	}
}

void ARocket_gamePawn::Tick(float DeltaSeconds)
{
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaSeconds, 0.f, 0.f);

	// Move plan forwards (with sweep so we stop when we collide with things)
	AddActorLocalOffset(LocalMove, true);

	// Calculate change in rotation this frame
	FRotator DeltaRotation(0,0,0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaSeconds;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;

	// Rotate plane
	AddActorLocalRotation(DeltaRotation);

	float NewForwardSpeed = CurrentForwardSpeed + (DeltaSeconds * Acceleration);
	// Clamp between MinSpeed and MaxSpeed
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);

	Super::Tick(DeltaSeconds);

	SaveGameLogic(DeltaSeconds);
	LoadGameLogic(DeltaSeconds);

	URocketGameInstance* GI = Cast<URocketGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UE_LOG(LogTemp, Warning, TEXT("coins: %d"), GI->coins);
}

void ARocket_gamePawn::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// Deflect along the surface when we collide.
	FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));
}


void ARocket_gamePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // Check if PlayerInputComponent is valid (not NULL)
	check(PlayerInputComponent);

	// Bind our control axis' to callback functions
	PlayerInputComponent->BindAxis("Thrust", this, &ARocket_gamePawn::ThrustInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &ARocket_gamePawn::MoveUpInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARocket_gamePawn::MoveRightInput);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ARocket_gamePawn::Shoot);
	PlayerInputComponent->BindAction("ShootRocket", IE_Pressed, this, &ARocket_gamePawn::ShootRocket);
	PlayerInputComponent->BindAction("LoadGame", IE_Pressed, this, &ARocket_gamePawn::SetLoadGame);
	PlayerInputComponent->BindAction("SaveGame", IE_Pressed, this, &ARocket_gamePawn::SetSaveGame);
}

void ARocket_gamePawn::ThrustInput(float Val)
{
	// Is there any input?
	//bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	// If input is not held down, reduce speed
	//float CurrentAcc = bHasInput ? (Val * Acceleration) : (-0.5f * Acceleration);
	// Calculate new speed
	//float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed
	//CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
}

void ARocket_gamePawn::MoveUpInput(float Val)
{
	// Target pitch speed is based in input
	float TargetPitchSpeed = (Val * TurnSpeed * -1.f);

	// When steering, we decrease pitch slightly
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);

	// Smoothly interpolate to target pitch speed
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ARocket_gamePawn::MoveRightInput(float Val)
{
	// Target yaw speed is based on input
	float TargetYawSpeed = (Val * TurnSpeed);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	// Is there any left/right input?
	const bool bIsTurning = FMath::Abs(Val) > 0.2f;

	// If turning, yaw value is used to influence roll
	// If not turning, roll to reverse current roll value.
	float TargetRollSpeed = bIsTurning ? (CurrentYawSpeed * 0.5f) : (GetActorRotation().Roll * -2.f);

	// Smoothly interpolate roll speed
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ARocket_gamePawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (Cast<APortal>(OtherActor) != nullptr)
	{
		score++;
	}*/
}

FString ARocket_gamePawn::GetScore()
{
	FString scoreR = "Score: " + FString::FromInt(score);
	
	return scoreR;
}

int ARocket_gamePawn::GetScoreInt()
{
	return score;
}

FString ARocket_gamePawn::GetScoreBoard(int i)
{
	URocketGameInstance* GI = Cast<URocketGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	FString scoreB = FString::FromInt(GI->scoreboard[i]);
	return scoreB;
}

void ARocket_gamePawn::PovecajScore()
{
	score = score + 1;
}

void ARocket_gamePawn::SetScore(int score1)
{
	score = score1;
}

void ARocket_gamePawn::SetScoreBoard(int* scoreboard)
{
	URocketGameInstance* GI = Cast<URocketGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	for (int i = 0; i < 11; i++)
	{
		GI->scoreboard[i] = scoreboard[i];
	}
}

void ARocket_gamePawn::SaveGameLogic(float dTime)
{
	if (canSaveGame)
	{
		savingSequanceTimer += 1 * dTime;

		if (savingSequanceTimer > 3.f)
		{
			InitSaveGame();

			savingSequanceTimer = 0.f;
			canSaveGame = false;
		}
		else
		{
			if (!isAssemblingSaveGameData)
			{
				if (this->IsValidLowLevel())
				{
					GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString(TEXT("Getting ready to save...")), true);
					isAssemblingSaveGameData = true;
				}
				else
				{
					savingSequanceTimer = 0.f;
					canSaveGame = false;
					isAssemblingSaveGameData = false; 
				}
			}
		}
	}
}

void ARocket_gamePawn::InitSaveGame()
{
	class UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

	if (SaveGameInstance->IsValidLowLevel())
	{
		SaveGameInstance->score = GetScoreInt();
		URocketGameInstance* GI = Cast<URocketGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		for (int i = 0; i < 11; i++)
		{
			SaveGameInstance->scoreboard[i] = GI->scoreboard[i];
		}
		UE_LOG(LogTemp, Warning, TEXT("coins: %d"), GI->coins);
		SaveGameInstance->coins = GI->coins;
		SaveGameInstance->coinsTest = GI->coinsTest;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "HighScore", 1);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString(TEXT("Game saved!")), true);
	}
	else
	{
		class UMySaveGame* SaveGameInstance_2 = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

		if (!SaveGameInstance_2) return;
		else
		{
			SaveGameInstance_2->score = GetScoreInt();
			URocketGameInstance* GI = Cast<URocketGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			for (int i = 0; i < 11; i++)
			{
				SaveGameInstance_2->scoreboard[i] = GI->scoreboard[i];
			}
			UE_LOG(LogTemp, Warning, TEXT("coins: %d"), GI->coins);
			SaveGameInstance_2->coins = GI->coins;
			SaveGameInstance_2->coinsTest = GI->coinsTest;
			UGameplayStatics::SaveGameToSlot(SaveGameInstance_2, "HighScore", 1);
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString(TEXT("Game saved!")), true);
		}
	}

}

void ARocket_gamePawn::LoadGameLogic(float dTime)
{
	if (zapocni_load)
	{
		loadingSequanceTimer += 1 * dTime;

		if (loadingSequanceTimer > 0.20f)
		{
			InitLoadGame();

			loadingSequanceTimer = 0.f;
			hasCompletedLoadGame = true;
			isAssemblingSaveGameData = false;
			zapocni_load = false;
		}
	}
}

void ARocket_gamePawn::InitLoadGame()
{
	if (this->IsValidLowLevel())
	{
		const FString SaveSlotName = FString(TEXT("HighScore"));

		if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 1))
		{
			class UMySaveGame* LoadInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
			if (LoadInstance->IsValidLowLevel())
			{
				LoadInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("HighScore", 1));
				SetScore(LoadInstance->score);

				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, FString(TEXT("Game loaded from save!")), true);

				SetScoreBoard(LoadInstance->scoreboard);
				URocketGameInstance* GI = Cast<URocketGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
				GI->coins = LoadInstance->coins;
				GI->coinsTest = LoadInstance->coinsTest;
				UE_LOG(LogTemp, Warning, TEXT("coins: %d"), GI->coins);
			}
			else {
				class UMySaveGame* LoadInstance_2 = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
				if (!LoadInstance_2) return;
				else
				{
					LoadInstance_2 = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("HighScore", 1));
					SetScore(LoadInstance_2->score);

					GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, FString(TEXT("Game loaded from save!")), true);

					SetScoreBoard(LoadInstance_2->scoreboard);
					URocketGameInstance* GI = Cast<URocketGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
					GI->coins = LoadInstance_2->coins;
					GI->coinsTest = LoadInstance_2->coinsTest;
					UE_LOG(LogTemp, Warning, TEXT("coins: %d"), GI->coins);
				}
			}
		}
	}
}