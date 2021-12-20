// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Rocket_gamePawn.generated.h"

UCLASS(Config=Game)
class ARocket_gamePawn : public APawn
{
	GENERATED_BODY()

	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PlaneMesh;

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent* Lights;

public:
	ARocket_gamePawn();

	// Begin AActor overrides
	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	// End AActor overrides
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Score")
	FString GetScore();

	int GetScoreInt();

	UFUNCTION(BlueprintPure, Category = "Score")
	FString GetScoreBoard(int i);

	void PovecajScore();

	void SetScore(int score1);

	void SetScoreBoard(int *scoreboard);

	UPROPERTY(EditAnywhere, Category = "MainHud")
	class UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainHud", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> MainHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainHud", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> MainMenuHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainHud", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HelpHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainHud", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> PauseHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainHud", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> EndHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainHud", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> LevelHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainHud", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> ScoreboardHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainHud", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> ShopHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainHud")
	int score;

	UFUNCTION(BlueprintCallable, Category = "Br_metaka")
	void UpdateBr_metaka(int metak, int raketa);

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	int br_metaka;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	int br_raketa;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	int max_metaka;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	int max_raketa;

	UFUNCTION(BlueprintPure, Category = "Br_metaka")
	int GetMax_metaka();

	UFUNCTION(BlueprintPure, Category = "Br_metaka")
	int GetBr_metaka();

	UFUNCTION(BlueprintPure, Category = "Br_metaka")
	int GetBr_raketa();

	UFUNCTION(BlueprintCallable, Category = "Component")
	void Destroy_Pawn();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void Start_Game();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void Back();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void Help_menu();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void Pause_Game();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UnPause_Game();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void Quit_game();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void Open_levels();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void Open_scoreboard();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void Open_level_test();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void Open_level_mainMenu();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void Open_shop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float health;

	void lowerHP();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHPPercent();

protected:

	// Begin APawn overrides
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override; // Allows binding actions/axes to functions
	// End APawn overrides

	/** Bound to the thrust axis */
	void ThrustInput(float Val);
	
	/** Bound to the vertical axis */
	void MoveUpInput(float Val);

	/** Bound to the horizontal axis */
	void MoveRightInput(float Val);

	//shooting
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void Shoot();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void ShootRocket();

	UFUNCTION(BlueprintCallable, Category = "save/load")
	void SetLoadGame();

	UFUNCTION(BlueprintCallable, Category = "save/load")
	void SetSaveGame();

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float Lokacija_Metka;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<class ABullet> BulletClass;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<class ARocket> RocketClass;

	UPROPERTY(EditAnywhere, Category = "Components")
	FTimerHandle PovecajHandle;

private:
	/** How quickly forward speed changes */
	UPROPERTY(Category=Plane, EditAnywhere)
	float Acceleration;

	/** How quickly pawn can steer */
	UPROPERTY(Category=Plane, EditAnywhere)
	float TurnSpeed;

	/** Max forward speed */
	UPROPERTY(Category = Pitch, EditAnywhere)
	float MaxSpeed;

	/** Min forward speed */
	UPROPERTY(Category=Yaw, EditAnywhere)
	float MinSpeed;

	/** Current forward speed */
	float CurrentForwardSpeed;

	/** Current yaw speed */
	float CurrentYawSpeed;

	/** Current pitch speed */
	float CurrentPitchSpeed;

	/** Current roll speed */
	float CurrentRollSpeed;

	bool flag;

	//Save &load var
	float loadingSequanceTimer;
	float savingSequanceTimer;
	bool hasCompletedLoadGame;
	bool isAssemblingSaveGameData;

	bool zapocni_load;
public:
	/** Returns PlaneMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetPlaneMesh() const { return PlaneMesh; }

	FORCEINLINE class UBoxComponent* GetBox() const { return Box; }

	/** Returns SpringArm subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SaveGameLogic(float dTime);
	void LoadGameLogic(float dTime);
	bool canSaveGame;

	void InitSaveGame();
	void InitLoadGame();

};
