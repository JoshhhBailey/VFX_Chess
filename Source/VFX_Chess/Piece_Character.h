// Fill out your copyright notice in the Description page of Project Settings.

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
