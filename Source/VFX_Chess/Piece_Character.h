/// \file Piece_Character.h
/// \brief Piece character logic
/// \author Dmitrii Shevchenko
/// \date 09/03/21 Updated to NCCA Coding standard
/// Revision History:
///
/// \todo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Piece.h"
#include "Piece_Character.generated.h"

UCLASS()
class VFX_CHESS_API APiece_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APiece_Character();
	// Piece 
	APiece* GetPiece() const {return Piece;}
	void SetPiece(APiece* _Piece) {this->Piece = _Piece;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	APiece* Piece;
};
