// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "containers/Array.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

		class USpringArmComponent;
		class UCameraComponent;

UCLASS()
class SESSION3_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	TArray<UStaticMeshComponent*> Spheres;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	UMaterial* Red;
	UPROPERTY(EditAnywhere)
	UMaterial* Blue;
	UPROPERTY(EditAnywhere)
	UMaterial* White;



	void OnePressed();
	void TwoPressed();
	void ThreePressed();
	void FourPressed();
	void FivePressed();
	void SixPressed();
	void SevenPressed();
	void EightPressed();
	void NinePressed();

	void restart();

	int TurnCounter;

	TArray<bool> SphereStatus;

	TArray<int> WinStatus;

	void TurnController(int SphereIndex);

	void WinCondition();
};
