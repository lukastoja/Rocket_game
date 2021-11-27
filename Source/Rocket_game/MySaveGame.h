// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ROCKET_GAME_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	

public:
	UMySaveGame();

public:

	UPROPERTY()
	int score;

	UPROPERTY()
	int scoreboard[11];

	UPROPERTY()
	int coins;
};
