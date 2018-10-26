// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ship.generated.h"

class ALazerBeam;

UCLASS()
class DODGER_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();

public:	

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ShipMesh;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* DeathSound;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* Explosion;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ALazerBeam> Lazer;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintPure)
	int GetScore() { return Score; }

	UFUNCTION(BlueprintCallable)
	void SetScore(int value) { Score = value; }

private:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Shoot();

	void MoveForward(float Value);

	void MoveRight(float Value);



	float MovementSpeed;
	FVector Direction;

	int Score;

	bool bCanFire;
	float FireRate;
	FTimerHandle ResetFireRateHandle;
	void ResetFireRateTimer();
};
