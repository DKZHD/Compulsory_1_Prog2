// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacToe.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATicTacToe::ATicTacToe()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Ball.Init(NULL, 9);
	Slot.Init(NULL, 9);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Ball[4] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("4"));
	SetRootComponent(Ball[4]);

	for (int i = 0; i < 9; i++)
	{
		if (i != 4)
		{
			Ball[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName(FString::FromInt(i)));
			Ball[i]->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			Slot[i] = false;
		}
		Ball[i]->SetStaticMesh(Sphere.Object);
	}

	Ball[0]->AddLocalOffset(FVector(-200.f, -200.f, 0));
	Ball[1]->AddLocalOffset(FVector(0.f, -200.f, 0));
	Ball[2]->AddLocalOffset(FVector(200.f, -200.f, 0));
	Ball[3]->AddLocalOffset(FVector(-200.f, 0.f, 0));
	Ball[5]->AddLocalOffset(FVector(200.f, 0.f, 0));
	Ball[6]->AddLocalOffset(FVector(-200.f, 200.f, 0));
	Ball[7]->AddLocalOffset(FVector(0.f, 200.f, 0));
	Ball[8]->AddLocalOffset(FVector(200.f, 200.f, 0));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->AddLocalRotation(FRotator(-90.f, 0.f, -90.f));
	SpringArm->TargetArmLength = 800;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ATicTacToe::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < 9; i++)
		Ball[i]->SetMaterial(0, White);
}

// Called every frame
void ATicTacToe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckWinner(Red, 0, 1, 2);
	CheckWinner(Blue, 0, 1, 2);

	CheckWinner(Red, 3, 4, 5);
	CheckWinner(Blue, 3, 4, 5);

	CheckWinner(Red, 6, 7, 8);
	CheckWinner(Blue, 6, 7, 8);

	CheckWinner(Red, 0, 3, 6);
	CheckWinner(Blue, 0, 3, 6);

	CheckWinner(Red, 1, 4, 7);
	CheckWinner(Blue, 1, 4, 7);

	CheckWinner(Red, 2, 5, 8);
	CheckWinner(Blue, 2, 5, 8);

	CheckWinner(Red, 0, 4, 8);
	CheckWinner(Blue, 0, 4, 8);

	CheckWinner(Red, 2, 4, 6);
	CheckWinner(Blue, 2, 4, 6);

		
	if (PlayerWin == 1)
	{
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Blue, TEXT("Player1 Win"));
		
	}
		
	else if(PlayerWin==2)
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, TEXT("Player2 Win"));
	else if(Draw())
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Magenta, TEXT("Draw"));
}

// Called to bind functionality to input
void ATicTacToe::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("1", IE_Pressed, this,&ATicTacToe::Key1);
	PlayerInputComponent->BindAction("2", IE_Pressed, this,&ATicTacToe::Key2);
	PlayerInputComponent->BindAction("3", IE_Pressed, this,&ATicTacToe::Key3);
	PlayerInputComponent->BindAction("4", IE_Pressed, this,&ATicTacToe::Key4);
	PlayerInputComponent->BindAction("5", IE_Pressed, this,&ATicTacToe::Key5);
	PlayerInputComponent->BindAction("6", IE_Pressed, this,&ATicTacToe::Key6);
	PlayerInputComponent->BindAction("7", IE_Pressed, this,&ATicTacToe::Key7);
	PlayerInputComponent->BindAction("8", IE_Pressed, this,&ATicTacToe::Key8);
	PlayerInputComponent->BindAction("9", IE_Pressed, this,&ATicTacToe::Key9);
}

void ATicTacToe::CheckWinner(UMaterial* color, int number1, int number2, int number3)
{
	if(Ball[number1]->GetMaterial(0)==color&&Ball[number2]->GetMaterial(0)==color&&Ball[number3]->GetMaterial(0)==color)
	{
		if (Ball[number1]->GetMaterial(0) == Blue)
			PlayerWin = 1;
		if (Ball[number1]->GetMaterial(0) == Red)
			PlayerWin = 2;
	}
}

void ATicTacToe::FillColor(int number)
{
	if(Slot[number]==false) {
		if (Active == true)
		{
			Ball[number]->SetMaterial(0, Blue);
			Active = false;
		}
			
	else if(Active==false)
	{
		Ball[number]->SetMaterial(0, Red);
		Active = true;
	}
		
	Slot[number] = true;
	}
}

void ATicTacToe::Key1()
{
	FillColor(0);
}

void ATicTacToe::Key2()
{
	FillColor(1);
}

void ATicTacToe::Key3()
{
	FillColor(2);
}

void ATicTacToe::Key4()
{
	FillColor(3);
}

void ATicTacToe::Key5()
{
	FillColor(4);
}

void ATicTacToe::Key6()
{
	FillColor(5);
}

void ATicTacToe::Key7()
{
	FillColor(6);
}

void ATicTacToe::Key8()
{
	FillColor(7);
}

void ATicTacToe::Key9()
{
	FillColor(8);
}

bool ATicTacToe::Draw()
{
	for (int i = 0; i < 9; i++)
	{
		if (Slot[i] == false)
			return false;
	}
	return true;
}
