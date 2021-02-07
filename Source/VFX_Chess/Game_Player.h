// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CoreMinimal.h"
#include "Game_Player.generated.h"

UCLASS()
class VFX_CHESS_API AGame_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGame_Player();

	void SetIsWhite(bool _bool) { m_isWhite = _bool; }

private:
	class AGame_Controller* m_gameController;
	class UCameraComponent* m_camera;
	class USpringArmComponent* m_cameraSpringArm;

	bool m_isWhite = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
