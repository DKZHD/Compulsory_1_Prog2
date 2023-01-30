// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TicTacToe.generated.h"

UCLASS()
class COMPULSORY_1_API ATicTacToe : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATicTacToe();
	UPROPERTY(EditAnywhere)
	TArray<UStaticMeshComponent*> Ball;
	UPROPERTY(EditAnywhere)
		class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
		class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
		UMaterial* Red;
	UPROPERTY(EditAnywhere)
		UMaterial* Blue;
	UPROPERTY(EditAnywhere)
		UMaterial* White;
	APlayerController* player;
	TArray<bool>Slot;
	int PlayerWin = 0;
	bool Active = true;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void CheckWinner(UMaterial* color,int number1,int number2,int number3);
	void FillColor(int number);
	void Key1();
	void Key2();
	void Key3();
	void Key4();
	void Key5();
	void Key6();
	void Key7();
	void Key8();
	void Key9();
	bool Draw();
};
