// Fill out your copyright notice in the Description page of Project Settings.


#include "Main.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <UObject/ConstructorHelpers.h>
#include "Containers/Array.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AMain::AMain()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Spheres.Init(NULL, 9);
	counter.Init(NULL, 9);
	Spheres[0] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
	Spheres[1] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	Spheres[2] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh3"));
	Spheres[3] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh4"));
	Spheres[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh5"));
	Spheres[5] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh6"));
	Spheres[6] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh7"));
	Spheres[7] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh8"));
	Spheres[8] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh9"));

	RootComponent = Spheres[4];
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
	MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	for (int i{}; i < 9; i++) {

		if (i != 4) {
			Spheres[i]->SetupAttachment(GetRootComponent());
		}
		Spheres[i]->SetStaticMesh(MeshComponentAsset.Object);
	}
	Red = CreateDefaultSubobject<UMaterial>(TEXT("RedMaterial"));
	Blue = CreateDefaultSubobject<UMaterial>(TEXT("BlueMaterial"));
	White = CreateDefaultSubobject<UMaterial>(TEXT("WhiteMaterial"));
	
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	Spheres[0]->SetRelativeLocation(FVector(200.f, -200.f, 0.f));
	Spheres[1]->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	Spheres[2]->SetRelativeLocation(FVector(200.f, 200.f, 0.f));
	Spheres[3]->SetRelativeLocation(FVector(0.f, -200.f, 0.f));
	Spheres[4]->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Spheres[5]->SetRelativeLocation(FVector(0.f, 200.f, 0.f));
	Spheres[6]->SetRelativeLocation(FVector(-200.f, -200.f, 0.f));
	Spheres[7]->SetRelativeLocation(FVector(-200.f, 0.f, 0.f));
	Spheres[8]->SetRelativeLocation(FVector(-200.f, 200.f, 0.f));
	TurnCounter = 0;
	SphereStatus.Init(NULL, 9);
	
}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();
	for (int i{}; i < 9; i++)
	{
		Spheres[i]->SetMaterial(0, White);
	}
}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ChangeColor", IE_Pressed, this, &AMain::ChangeColor);
	PlayerInputComponent->BindAction("1", IE_Pressed, this, &AMain::OnePressed);
	PlayerInputComponent->BindAction("2", IE_Pressed, this, &AMain::TwoPressed);
	PlayerInputComponent->BindAction("3", IE_Pressed, this, &AMain::ThreePressed);
	PlayerInputComponent->BindAction("4", IE_Pressed, this, &AMain::FourPressed);
	PlayerInputComponent->BindAction("5", IE_Pressed, this, &AMain::FivePressed);
	PlayerInputComponent->BindAction("6", IE_Pressed, this, &AMain::SixPressed);
	PlayerInputComponent->BindAction("7", IE_Pressed, this, &AMain::SevenPressed);
	PlayerInputComponent->BindAction("8", IE_Pressed, this, &AMain::EightPressed);
	PlayerInputComponent->BindAction("9", IE_Pressed, this, &AMain::NinePressed);

}
void AMain::ChangeColor() 
{
	
	Mesh->SetMaterial(0, Red);
}
void AMain::OnePressed()
{
	TurnController(0);
}

void AMain::TwoPressed()
{
	TurnController(1);
}

void AMain::ThreePressed()
{
	TurnController(2);
}

void AMain::FourPressed()
{
	TurnController(3);
}

void AMain::FivePressed()
{
	TurnController(4);
}

void AMain::SixPressed()
{
	TurnController(5);
}

void AMain::SevenPressed()
{
	TurnController(6);
}

void AMain::EightPressed()
{
	TurnController(7);
}

void AMain::NinePressed()
{
	TurnController(8);
}
void AMain::TurnController(int sphereindex) {


	if (SphereStatus[sphereindex] == true)
	{
	
		UE_LOG(LogTemp, Warning, TEXT("That index is already taken"));

		if (!redVictory && !blueVictory && TurnCounter == 9) {
			UE_LOG(LogTemp, Warning, TEXT("DRAW!"));
			return;
		}
		return;
	}


	if (TurnCounter % 2 == 0 && !redVictory)
	{
		Spheres[sphereindex]->SetMaterial(0, Blue);
		counter[sphereindex] = blueID;
			CheckWinner();
		// assign a id to the blue positon and if it has same ID in a row then the game is won

	}
	else if (TurnCounter % 2 == 1 && !blueVictory)
	{
		Spheres[sphereindex]->SetMaterial(0, Red);
		counter[sphereindex] = redID;
		CheckWinner();
	}
	SphereStatus[sphereindex] = true;
	TurnCounter++;
	CheckWinner();
	
}
void AMain::CheckWinner() {
	
	
	if (counter[0] == blueID && counter[1] == blueID && counter[2] == blueID || counter[3] == blueID && counter[4] == blueID && counter[5] == blueID || counter[6] == blueID && counter[7] == blueID && counter[8] == blueID || //horizontal check
		counter[0] == blueID && counter[3] == blueID && counter[6] == blueID || counter[1] == blueID && counter[4] == blueID && counter[7] == blueID || counter[2] == blueID && counter[5] == blueID && counter[8] == blueID || // vertical check
		counter[0] == blueID && counter[4] == blueID && counter[8] == blueID || counter[2] == blueID && counter[4] == blueID && counter[6] == blueID) // diagonal check
	{
		//blue wins
		blueVictory = true;
		UE_LOG(LogTemp, Warning, TEXT("Blue wins!"));
	}
	if (counter[0] == redID && counter[1] == redID && counter[2] == redID || counter[3] == redID && counter[4] == redID && counter[5] == redID || counter[6] == redID && counter[7] == redID && counter[8] == redID || //horizontal check
		counter[0] == redID && counter[3] == redID && counter[6] == redID || counter[1] == redID && counter[4] == redID && counter[7] == redID || counter[2] == redID && counter[5] == redID && counter[8] == redID || // vertical check
		counter[0] == redID && counter[4] == redID && counter[8] == redID || counter[2] == redID && counter[4] == redID && counter[6] == redID) // diagonal check
	{
		//red wins
		redVictory = true;
		UE_LOG(LogTemp, Warning,TEXT("Red wins!"));
	}

		
		
		//


}

