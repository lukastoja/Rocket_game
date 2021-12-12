// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketGameInstance.h"

URocketGameInstance::URocketGameInstance()
{
	score = 0;
	for (int32 i = 0; i < 11; i++)
	{
		scoreboard[i] = 0;
	}
	coins = 0;

	coinsTest = 0;

	UE_LOG(LogTemp, Warning, TEXT("treba se pozvati sam ojedno pizda"));
}

void URocketGameInstance::sortScoreboard()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (scoreboard[j] < scoreboard[j + 1])
			{
				int tmp = scoreboard[j];
				scoreboard[j] = scoreboard[j + 1];
				scoreboard[j + 1] = tmp;
			}
		}

	}
}

void URocketGameInstance::setCoins()
{
	UE_LOG(LogTemp, Warning, TEXT("coins: %d, score: %d"), coins, score);
	coins = coins + (score / 10);
}

void URocketGameInstance::setCoinsTest()
{
	coinsTest = coinsTest + (score / 10);
}
