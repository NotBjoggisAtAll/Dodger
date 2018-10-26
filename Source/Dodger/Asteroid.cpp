// Fill out your copyright notice in the Description page of Project Settings.

#include "Asteroid.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "InvisibleWall.h"

// Sets default values
AAsteroid::AAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AsteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Asteroid Mesh"));

	RootComponent = AsteroidMesh;
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	
	AsteroidMesh->OnComponentBeginOverlap.AddDynamic(this, &AAsteroid::OnOverlapBegin);

	FallSpeed = UKismetMathLibrary::RandomFloatInRange(500.f, 3000.f);
	FallRotation = UKismetMathLibrary::RandomFloatInRange(-450.f, 450.f);
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() - FVector(FallSpeed * DeltaTime, 0.f, 0.f));
	SetActorRotation(GetActorRotation() - FRotator(0.f, 0.f, FallRotation * DeltaTime));
}

//Called when overlapping with something
void AAsteroid::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto Wall = Cast<AInvisibleWall>(OtherActor);
	if (Wall)
	{
		Destroy();
	}
}

