/// \file Game_Player.h
/// \brief Player camera settings
/// \author Josh Bailey
/// \date 09/03/21 Updated to NCCA Coding standard
/// Revision History:
///
/// \todo

#pragma once

#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CoreMinimal.h"
#include "Game_Player.generated.h"

UCLASS()
class VFX_CHESS_API AGame_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGame_Player();

	void SetSpringArmLength(float _interval) { m_cameraSpringArm->TargetArmLength += _interval; }
	float GetSpringArmLength() { return m_cameraSpringArm->TargetArmLength; }

	USpringArmComponent* GetSpringArm() { return m_cameraSpringArm; }

private:
	class AGame_Controller* m_gameController;
	UCameraComponent* m_camera;
	USpringArmComponent* m_cameraSpringArm;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};