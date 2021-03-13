/// \file Game_Controller.h
/// \brief Handles all game rules and logic. Core of program.
/// \author Josh Bailey and Dmitrii Shevchenko
/// \date 09/03/21 Updated to NCCA Coding standard
/// Revision History:
///
/// \todo

#pragma once

#include "Board.h"

#include <algorithm>	// std::unique
#include <string>

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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void WhiteWin();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BlackWin();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void Stalemate();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PlayMovePieceSound();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PlayCheckSound();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PlayPieceTaken(int _pieceID, bool _isWhite);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PromotedPieceUI(bool _isWhite);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CallCutscene(int _index);

	UFUNCTION(BlueprintCallable)
		int PromotePawn(int _pieceID);

	UFUNCTION(BlueprintCallable)
		bool getWhiteMove() { return m_whiteMove; }

private:
	// Initialisation
	ABoard* m_board;
	bool m_whiteMove = true;

	// Cameras
	class AGame_Player* m_cameraOne;
	class AGame_Player* m_cameraTwo;
	class AGame_Player* m_camera;
	float m_blendTime = 2.0f;

	// Mouse input
	class APiece* m_selectedPiece;
	class ABoard_Square* m_selectedSquare;
	FHitResult m_target;
	class APiece* m_targetPiece;

	std::vector<std::vector<int>> m_availableMovesCopy;		// Copy of ALL best case scenario possible moves for a piece
	std::vector<int> m_filteredMoves;											// Filter out moves (being blocked by other pieces)
	std::vector<int> m_validMoves;												// Filter out moves that will cause check on self
	bool m_movesHighlighted = false;

	// Active pieces on the board
	// ID's: 0-7 = Pawn, 8-9 = Rook, 10-11 = Knight, 12-13 = Bishop, 14 = Queen, 15 = King
	std::vector<APiece*> m_whitePieces;
	std::vector<APiece*> m_blackPieces;

	// Squares being attacked
	std::vector<int> m_whiteAttacking;
	std::vector<int> m_blackAttacking;

	// Check
	bool m_whiteCheck = false;
	bool m_blackCheck = false;

	// Castling
	bool m_whiteKingSideCastle = true;
	bool m_whiteQueenSideCastle = true;
	bool m_blackKingSideCastle = true;
	bool m_blackQueenSideCastle = true;

	// En Passant
	APiece* m_enPassantVictim;
	bool m_enPassant = false;
	bool m_promoting = false;

	bool m_gameOver = false;

	TMap<FString, int> m_cutsceneSelection = {
		{"03", 0},	// Pawn Vs Rook
		{"12", 1},	// Knight Vs Bishop
		{"21", 2},	// Bishop Vs Knight
		/*{"33", 3}*/		// Rook Vs Rook
	};

	// Spawning
	void SpawnPiece(std::string _name, bool _isWhite, int _squareID, int _pieceID, FString _cutsceneID, int xPos, int yPos, FRotator _rot, bool _promoting);
	void SpawnPieces();

	// Mouse input
	void LeftMouseClick();
	void RightMouseDown();
	void RightMouseUp();
	void ZoomIn();
	void ZoomOut();
	void SelectPiece();
	bool SelectSquare(bool _enemyPieceSelected);

	// Keyboard input
	void RotateCameraLeft();
	void RotateCameraRight();
	void RotateCameraUp();
	void RotateCameraDown();

	// Show / hide moves
	void HighlightMoves();
	void UnhighlightMoves();

	// Move simulation
	std::vector<int> CalculateAttackingMoves(bool _isWhite);
	bool CheckKingAttack(bool _isWhite, std::vector<int> _attackedSquares);
	void SimulateMove(APiece* _piece, int _move);
	std::vector<int> FilterSimulatedMoves(std::vector<std::vector<int>> _unfilteredMoves, bool _isWhite);
	std::vector<int> FilterRealMoves(APiece* _piece, std::vector<std::vector<int>> _movesToFilter);
	
	// Check / Checkmate
	bool CheckSelfForCheck();
	void MoveOutOfCheck(std::vector<APiece*> _pieces);
	void CheckForCheckmate();
	void CheckForStalemate();

	// Castling
	void CalculateCastleKingSide(int _rookPos, int _knightPos, int _bishopPos, std::vector<int> &_opponentAttacking);
	void CalculateCastleQueenSide(int _rookPos, int _knightPos, int _bishopPos, int _queenPos, std::vector<int> &_opponentAttacking);
	void Castle(int _rookPos, int _rookTarget);

	void EnPassant();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};