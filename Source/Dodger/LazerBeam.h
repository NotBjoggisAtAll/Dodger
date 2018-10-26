// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LazerBeam.generated.h"

UCLASS()
class DODGER_API ALazerBeam : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALazerBeam();

public:
	UPROPERTY(EditDefaultsOnly)
		USoundBase* ShootSound;

	UPROPERTY(EditDefaultsOnly)
		USoundBase* AsteroidSound;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* Explosion;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* LazerMesh;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	void IncrementScore();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
