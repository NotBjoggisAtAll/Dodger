// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SaveHighscore.h"
#include "DodgerGameModeBase.generated.h"

UCLASS()
class DODGER_API ADodgerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		ADodgerGameModeBase();

	virtual void BeginPlay() override;

	void GetHighscoreFromFile();

	void SaveFile();

	void LoadFile();

	USaveHighscore* HighScoreSave;

	int HighScore;

public:
	UFUNCTION(BlueprintPure)
	int GetHighScore() { return HighScore; }


	void UpdateHighscoreToFile(int NewHighScore);
};
