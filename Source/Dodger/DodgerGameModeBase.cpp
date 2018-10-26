// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgerGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ADodgerGameModeBase::ADodgerGameModeBase()
{}

void ADodgerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetHighscoreFromFile();
}
void ADodgerGameModeBase::UpdateHighscoreToFile(int NewHighScore)
{
	LoadFile();
	if (NewHighScore > HighScoreSave->HighScore)
	{
		HighScoreSave->HighScore = NewHighScore;
		UE_LOG(LogTemp, Warning, TEXT("New highscore! Updated the save with: %i"), NewHighScore);
	}
	SaveFile();
}
void ADodgerGameModeBase::GetHighscoreFromFile()
{
	LoadFile();
	UE_LOG(LogTemp, Warning, TEXT("Got highscore from savefile: "), HighScoreSave->HighScore);
	HighScore = HighScoreSave->HighScore;
}

void ADodgerGameModeBase::SaveFile()
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to save savefile"));
	if (UGameplayStatics::SaveGameToSlot(HighScoreSave, HighScoreSave->SaveSlotName, HighScoreSave->UserIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Savefile successfully saved"));
	}
}

void ADodgerGameModeBase::LoadFile()
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to load savefile"));
	HighScoreSave = Cast<USaveHighscore>(UGameplayStatics::CreateSaveGameObject(USaveHighscore::StaticClass()));
	HighScoreSave = Cast<USaveHighscore>(UGameplayStatics::LoadGameFromSlot(HighScoreSave->SaveSlotName, HighScoreSave->UserIndex));
	if (HighScoreSave == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't load save savefile, creating a new savefile"));
		HighScoreSave = Cast<USaveHighscore>(UGameplayStatics::CreateSaveGameObject(USaveHighscore::StaticClass()));
	}
	UE_LOG(LogTemp, Warning, TEXT("Savefile successfully loaded"));
}