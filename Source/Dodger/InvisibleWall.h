// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "InvisibleWall.generated.h"

UCLASS()
class DODGER_API AInvisibleWall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInvisibleWall();

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* Wall;

};
