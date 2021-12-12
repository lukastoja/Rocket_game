// Fill out your copyright notice in the Description page of Project Settings.


#include "MySaveGame.h"

UMySaveGame::UMySaveGame()
{
	score = 0;

	for (int i = 0; i < 11; i++)
	{
		scoreboard[i] = 0;
	}

	coins = 0;
	coinsTest = 0;
}
