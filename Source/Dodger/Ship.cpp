// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Sound/SoundBase.h"
#include "SaveHighscore.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Asteroid.h"

// Sets default values
AShip::AShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Super Mesh"));
	ShipMesh->SetRelativeScale3D(FVector(0.2f));

	RootComponent = ShipMesh;


	MovementSpeed = 2000.f;
	Direction = FVector(0.f);
	Score = 0;
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();

	ShipMesh->OnComponentBeginOverlap.AddDynamic(this, &AShip::OnOverlapBegin);
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + Direction.GetSafeNormal() * MovementSpeed * DeltaTime);
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShip::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShip::MoveRight);
}

void AShip::MoveForward(float Value)
{
	Direction.X = Value;
	//AddMovementInput(FVector(1.f, 0.f, 0.f), Value * MovementSpeed);
//	AddActorLocalOffset(FVector(Value * MovementSpeed, 0.f, 0.f), true);
}
void AShip::MoveRight(float Value)
{
	//AddMovementInput(FVector(0.f, 1.f, 0.f), Value * MovementSpeed);
	Direction.Y = Value;
	//	AddActorLocalOffset(FVector(0.f, Value * MovementSpeed, 0.f), true);
}

void AShip::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto Asteroid = Cast<AAsteroid>(OtherActor);
	if (Asteroid)
	{
		if (DeathSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), DeathSound, 0.7f);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't find Death Sound"));
		}
		if (Explosion)
		{
			FTransform ExplosionTransform = FTransform(GetActorRotation(), GetActorLocation(), FVector(5.f));
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, ExplosionTransform);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't find Particle System"));
		}

		USaveHighscore* HighScoreSave = Cast<USaveHighscore>(UGameplayStatics::CreateSaveGameObject(USaveHighscore::StaticClass()));
		HighScoreSave = Cast<USaveHighscore>(UGameplayStatics::LoadGameFromSlot(HighScoreSave->SaveSlotName, HighScoreSave->UserIndex));
		if (HighScoreSave == nullptr)
		{
			HighScoreSave = Cast<USaveHighscore>(UGameplayStatics::CreateSaveGameObject(USaveHighscore::StaticClass()));
		}
		else
		{

			if (Score > HighScoreSave->HighScore)
			{
				UE_LOG(LogTemp, Warning, TEXT("New Highscore, save file."));
				HighScoreSave->HighScore = Score;
				UGameplayStatics::SaveGameToSlot(HighScoreSave, HighScoreSave->SaveSlotName, HighScoreSave->UserIndex);
			}
		}




		Destroy();
	}
}

