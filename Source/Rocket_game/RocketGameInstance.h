// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RocketGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROCKET_GAME_API URocketGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	URocketGameInstance();

	int32 score;
	int32 scoreboard[11];

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coins")
	int32 coins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coins")
	int32 coinsTest;

	void sortScoreboard();
	void setCoins();
	void setCoinsTest();
};
