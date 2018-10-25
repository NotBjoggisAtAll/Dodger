// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Sound/SoundBase.h"
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

	DeathSound = CreateDefaultSubobject<USoundBase>(TEXT("MySound"));
	
	RootComponent = ShipMesh;


	MovementSpeed = 15.f;

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
	AddActorLocalOffset(FVector(Value * MovementSpeed, 0.f, 0.f), true);
}
void AShip::MoveRight(float Value)
{
	AddActorLocalOffset(FVector(0.f, Value * MovementSpeed, 0.f), true);
}

void AShip::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto Asteroid = Cast<AAsteroid>(OtherActor);
	if (Asteroid)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), DeathSound);
			Destroy();
	}
}

