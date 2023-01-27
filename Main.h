// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Main.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UMaterial;

UCLASS()
class SESSION2_API AMain : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMain();

	

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
	
	
private:
	UPROPERTY(meta = (AllowPrivateAccess = "true"),VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	
	UPROPERTY(EditAnywhere)
		UMaterial* Red;
	UPROPERTY(EditAnywhere)
		UMaterial* Blue;
	UPROPERTY(EditAnywhere)
		UMaterial* White;
	
	int TurnCounter;
	TArray<bool> SphereStatus;
	TArray<int> counter;
	bool redVictory;
	bool blueVictory;
	int redID = 10;
	int blueID = 11;

	void CheckWinner();
	void TurnController(int sphereindex);
	void ChangeColor();
	void OnePressed();
	void TwoPressed();
	void ThreePressed();
	void FourPressed();
	void FivePressed();
	void SixPressed();
	void SevenPressed();
	void EightPressed();
	void NinePressed();
};
