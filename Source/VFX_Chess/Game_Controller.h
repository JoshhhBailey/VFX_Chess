// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Board.h"

#include <algorithm>	// std::unique

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
	// Board and player initialisation
	ABoard* m_board;
	class AGame_Player* m_playerOne;
	class AGame_Player* m_playerTwo;
	bool m_whiteMove = true;

	// Mouse input
	class APiece* m_selectedPiece;
	class ABoard_Square* m_selectedSquare;
	FHitResult m_target;

	std::vector<std::vector<int>> m_availableMovesCopy;		// Copy of ALL best case scenario possible moves for a piece
	std::vector<int> m_filteredMoves;											// Filter out moves (being blocked by other pieces)
	std::vector<int> m_validMoves;												// Filter out moves that will cause check on self
	bool m_movesHighlighted = false;

	// Active pieces on the board
	// 0-7 = Pawn, 8-9 = Rook, 10-11 = Knight, 12-13 = Bishop, 14 = Queen, 15 = King
	std::vector<APiece*> m_whitePieces;
	std::vector<APiece*> m_blackPieces;

	// Squares being attacked
	std::vector<int> m_whiteAttacking;
	std::vector<int> m_blackAttacking;

	bool m_whiteCheck = false;
	bool m_blackCheck = false;

	void SpawnPieces();

	// Mouse input
	void LeftMouseClick();
	void SelectPiece();
	void SelectSquare();

	// Show / hide moves
	void HighlightMoves();
	void UnhighlightMoves();

	// Move simulation
	bool CalculateAttackingMoves(bool _isWhite);
	void SimulateMove(APiece* _piece, int _move);
	std::vector<int> FilterSimulatedMoves(std::vector<std::vector<int>> _unfilteredMoves, bool _isWhite);
	std::vector<int> FilterRealMoves(APiece* _piece, std::vector<std::vector<int>> _movesToFilter);
	
	// Check / Checkmate
	bool CheckSelfForCheck();
	void MoveOutOfCheck(std::vector<APiece*> _pieces);
	void CheckForCheckmate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
