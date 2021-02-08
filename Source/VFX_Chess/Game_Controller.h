// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Board.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Game_Controller.generated.h"

UCLASS()
class VFX_CHESS_API AGame_Controller : public APlayerController
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGame_Controller();

private:
	ABoard* m_board;
	class APiece* m_selectedPiece;
	class ABoard_Square* m_selectedSquare;

	class AGame_Player* m_playerOne;
	class AGame_Player* m_playerTwo;

	std::vector<int> m_availableMovesCopy;
	bool m_movesHighlighted = false;

	FHitResult m_target;

	void SpawnPieces();
	void LeftMouseClick();
	void SelectPiece();
	void SelectSquare();
	void HighlightMoves();
	void UnhighlightMoves();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
