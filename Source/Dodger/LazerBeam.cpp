// Fill out your copyright notice in the Description page of Project Settings.

#include "LazerBeam.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Asteroid.h"
#include "Kismet/KismetMathLibrary.h"
#include "Ship.h"

// Sets default values
ALazerBeam::ALazerBeam()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LazerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LazerMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	LazerMesh->SetStaticMesh(CubeMeshAsset.Object);

	LazerMesh->SetRelativeScale3D(FVector(1.f, 0.4f, 0.4f));

	RootComponent = LazerMesh;
}

// Called when the game starts or when spawned
void ALazerBeam::BeginPlay()
{
	Super::BeginPlay();

	LazerMesh->OnComponentBeginOverlap.AddDynamic(this, &ALazerBeam::OnOverlapBegin);
	float RandomPitch = UKismetMathLibrary::RandomFloatInRange(0.9f, 1.1f);
	UGameplayStatics::PlaySound2D(GetWorld(), ShootSound, 1.f, RandomPitch);

}

void ALazerBeam::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto Asteroid = Cast<AAsteroid>(OtherActor);
	if (Asteroid)
	{
		if (AsteroidSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), AsteroidSound);

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't find Asteroid Sound"));
		}
		if (Explosion)
		{
			FRotator ExplosionRotation = UKismetMathLibrary::RandomRotator();
			FVector ExplosionLocation = GetActorLocation();
			FVector ExplosionScale = Asteroid->GetActorScale3D() - 1.5f;
			FTransform ExplosionTransform = FTransform(GetActorRotation(), ExplosionLocation, ExplosionScale);

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, ExplosionTransform);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't find Particle System"));
		}
		Asteroid->Destroy();

		IncrementScore();
	}
	Destroy();
}

void ALazerBeam::IncrementScore()
{
	auto Ship = Cast<AShip>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Ship)
	{
		Ship->SetScore(Ship->GetScore() + 1);
	}
}