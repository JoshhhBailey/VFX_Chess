// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Player.h"
#include "Game_Controller.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AGame_Player::AGame_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	m_cameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	m_cameraSpringArm->SetupAttachment(RootComponent);
	m_cameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	m_cameraSpringArm->bDoCollisionTest = false;
	m_cameraSpringArm->TargetArmLength = 400.f;
	m_cameraSpringArm->bEnableCameraLag = true;
	m_cameraSpringArm->CameraLagSpeed = 3.0f;

	m_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	m_camera->SetupAttachment(m_cameraSpringArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AGame_Player::BeginPlay()
{
	Super::BeginPlay();
	m_gameController = Cast<AGame_Controller>(GetController());
}

// Called every frame
void AGame_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGame_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

