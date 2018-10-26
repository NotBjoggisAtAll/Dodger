// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Sound/SoundBase.h"
#include "SaveHighscore.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Asteroid.h"
#include "TimerManager.h"
#include "DodgerGameModeBase.h"
#include "LazerBeam.h"

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
	FireRate = 0.1f;
	bCanFire = true;
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

	Move(DeltaTime);
}

void AShip::Move(float DeltaTime)
{
	SetActorLocation(GetActorLocation() + Direction.GetSafeNormal() * MovementSpeed * DeltaTime, true);
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShip::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShip::MoveRight);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AShip::Shoot);

}

void AShip::Shoot()
{
	if (bCanFire == true)
	{
		bCanFire = false;
		FVector LocationOffset = FVector(400.f, 0.f, 0.f);

		FRotator Rotation = GetActorRotation();
		FVector Location = GetActorLocation() + LocationOffset;

		GetWorld()->SpawnActor<ALazerBeam>(Lazer, Location, Rotation);

		GetWorld()->GetTimerManager().SetTimer(ResetFireRateHandle, this, &AShip::ResetFireRateTimer, FireRate );
	}
}

void AShip::MoveForward(float Value)
{
	Direction.X = Value;
}
void AShip::MoveRight(float Value)
{
	Direction.Y = Value;
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

		auto GameMode = Cast<ADodgerGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->UpdateHighscoreToFile(Score);

		Destroy();
	}
}

void AShip::ResetFireRateTimer()
{
	bCanFire = true;
}

