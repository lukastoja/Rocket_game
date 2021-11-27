// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RocketGameState.generated.h"

/**
 * 
 */
UCLASS()
class ROCKET_GAME_API ARocketGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	ARocketGameState();

	int32 score;

private:


};
