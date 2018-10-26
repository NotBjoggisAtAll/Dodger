// Fill out your copyright notice in the Description page of Project Settings.

#include "InvisibleWall.h"

// Sets default values
AInvisibleWall::AInvisibleWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Wall = CreateDefaultSubobject<UBoxComponent>(TEXT("Wall"));
	Wall->SetBoxExtent(FVector(4000.f, 100.f, 500.f));
	RootComponent = Wall;

}
