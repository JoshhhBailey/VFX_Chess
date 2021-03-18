///
///  @file Piece_Bishop.cpp
///  @brief Piece character logic

#include "Piece_Character.h"

// Sets default values
APiece_Character::APiece_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APiece_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APiece_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APiece_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
