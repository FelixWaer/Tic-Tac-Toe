// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <UObject/ConstructorHelpers.h>
#include "Containers/Array.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spheres.Init(NULL, 9);
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
		for (int i = 0; i < 9; i++)
		{
			if (i != 4)
			{
				Spheres[i]->SetupAttachment(GetRootComponent());
			}
			Spheres[i]->SetStaticMesh(MeshComponentAsset.Object);
		}



	Red = CreateDefaultSubobject<UMaterial>(TEXT("RedMaterial"));
	Blue = CreateDefaultSubobject<UMaterial>(TEXT("BlueMaterial"));
	White = CreateDefaultSubobject<UMaterial>(TEXT("WhiteMaterial"));


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 500.f;

	// Attach the Camera to SpringArm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);



	Spheres[0]->SetRelativeLocation(FVector(200.f, -200.f, 0.f));
	Spheres[1]->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	Spheres[2]->SetRelativeLocation(FVector(200.f, 200.f, 0.f));
	Spheres[3]->SetRelativeLocation(FVector(0.f, -200.f, 0.f));
	Spheres[4]->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Spheres[5]->SetRelativeLocation(FVector(0.f, 200.f, 0.f));
	Spheres[6]->SetRelativeLocation(FVector(-200.f, -200.f, 0.f));
	Spheres[7]->SetRelativeLocation(FVector(-200.f, 0.f, 0.f));
	Spheres[8]->SetRelativeLocation(FVector(-200.f, 200.f, 0.f));

	SphereStatus.Init(false, 9);
	WinStatus.Init(0, 9);
	Rows.Init(0, 8);

	TurnCounter = 0;


}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 9; i++)
	{
		Spheres[i]->SetMaterial(0, White);
	}
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("1", IE_Pressed, this, &AMyPawn::OnePressed);
	PlayerInputComponent->BindAction("2", IE_Pressed, this, &AMyPawn::TwoPressed);
	PlayerInputComponent->BindAction("3", IE_Pressed, this, &AMyPawn::ThreePressed);
	PlayerInputComponent->BindAction("4", IE_Pressed, this, &AMyPawn::FourPressed);
	PlayerInputComponent->BindAction("5", IE_Pressed, this, &AMyPawn::FivePressed);
	PlayerInputComponent->BindAction("6", IE_Pressed, this, &AMyPawn::SixPressed);
	PlayerInputComponent->BindAction("7", IE_Pressed, this, &AMyPawn::SevenPressed);
	PlayerInputComponent->BindAction("8", IE_Pressed, this, &AMyPawn::EightPressed);
	PlayerInputComponent->BindAction("9", IE_Pressed, this, &AMyPawn::NinePressed);

	PlayerInputComponent->BindAction("R", IE_Pressed, this, &AMyPawn::restart);
}

void AMyPawn::OnePressed()
{
	TurnController(0);
}

void AMyPawn::TwoPressed()
{
	TurnController(1);
}

void AMyPawn::ThreePressed()
{
	TurnController(2);
}

void AMyPawn::FourPressed()
{
	TurnController(3);
}

void AMyPawn::FivePressed()
{
	TurnController(4);
}

void AMyPawn::SixPressed()
{
	TurnController(5);
}

void AMyPawn::SevenPressed()
{
	TurnController(6);
}

void AMyPawn::EightPressed()
{
	TurnController(7);
}

void AMyPawn::NinePressed()
{
	TurnController(8);
}

void AMyPawn::restart()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Restarted"));
	for (int i = 0; i < 9; i++)
	{
		SphereStatus[i] = false;
		WinStatus[i] = 0;
		Spheres[i]->SetMaterial(0, White);
	}
	for (int j = 0; j < 8; j++)
	{
		Rows[j] = 0;
	}
	TurnCounter = 0;
}


void AMyPawn::TurnController(int SphereIndex)
{
	if (SphereStatus[SphereIndex] == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("That is already taken %d"), SphereIndex);
		return;
	}

	if (TurnCounter%2 == 0)
	{
		Spheres[SphereIndex]->SetMaterial(0, Blue);
		WinStatus[SphereIndex] = 1;
	}
	else
	{
		Spheres[SphereIndex]->SetMaterial(0, Red);
		WinStatus[SphereIndex] = -1;
	}

	SphereStatus[SphereIndex] = true;
	TurnCounter++;
	WinCondition();
}

void AMyPawn::WinCondition()
{
	Rows[0] = WinStatus[0] + WinStatus[1] + WinStatus[2];
	Rows[1] = WinStatus[3] + WinStatus[4] + WinStatus[5];
	Rows[2] = WinStatus[6] + WinStatus[7] + WinStatus[8];
	Rows[3] = WinStatus[0] + WinStatus[3] + WinStatus[6];
	Rows[4] = WinStatus[1] + WinStatus[4] + WinStatus[7];
	Rows[5] = WinStatus[2] + WinStatus[5] + WinStatus[8];
	Rows[6] = WinStatus[0] + WinStatus[4] + WinStatus[8];
	Rows[7] = WinStatus[2] + WinStatus[4] + WinStatus[6];

	for (int i = 0; i < 8; i++)
	{
		if (Rows[i] == 3)
		{
			UE_LOG(LogTemp, Warning, TEXT("Blue player has won"));
		}
		else if(Rows[i] == -3)
		{
			UE_LOG(LogTemp, Warning, TEXT("Red player has won"));
		}
	}
}
