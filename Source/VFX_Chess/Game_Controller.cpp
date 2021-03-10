///
///  @file Game_Controller.cpp
///  @brief Handles all game rules and logic. Core of program.

#include "Game_Controller.h"
#include "Game_Player.h"
#include "Piece.h"
#include "Piece_Pawn.h"
#include "Piece_Rook.h"
#include "Piece_Bishop.h"
#include "Piece_Knight.h"
#include "Piece_Queen.h"
#include "Piece_King.h"

// Sets default values
AGame_Controller::AGame_Controller()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mouse cursor options
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

// Called when the game starts or when spawned
void AGame_Controller::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetName() == "Main_Level")
	{
		// Spawn board
		m_board = GetWorld()->SpawnActor<ABoard>(FVector::ZeroVector, FRotator::ZeroRotator);
		// Spawn cameras
		m_cameraOne = GetWorld()->SpawnActor<AGame_Player>(FVector(200.0f, 100.0f, 200.0f), FRotator(0, 90.0f, 0));
		m_cameraOne->SetPivotOffset({200.0f, 0.0f, 0.0f});
		m_cameraTwo = GetWorld()->SpawnActor<AGame_Player>(FVector(200.0f, 400.0f, 200.0f), FRotator(0, -90.0f, 0));
		m_cameraTwo->SetPivotOffset({-200.0f, 0.0f, 0.0f});

		Possess(m_cameraOne);

		SpawnPieces();
		UE_LOG(LogTemp, Warning, TEXT("Game has started."));
	}
}

void AGame_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setup inputs
	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AGame_Controller::LeftMouseClick);
	InputComponent->BindAction("RightMouseClick", IE_Pressed, this, &AGame_Controller::RightMouseClick);
	InputComponent->BindAction("ScrollUp", IE_Pressed, this, &AGame_Controller::ScrollUp);
	InputComponent->BindAction("ScrollDown", IE_Pressed, this, &AGame_Controller::ScrollDown);
}

// Called every frame
void AGame_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGame_Controller::SpawnPiece(std::string _name, bool _isWhite, int _squareID, int _pieceID, int xPos, int yPos, FRotator _rot, bool _promoting = false)
{
	APiece *piece = nullptr;
	if (_name == "Pawn")
	{
		piece = GetWorld()->SpawnActor<APiece_Pawn>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	else if (_name == "Knight")
	{
		piece = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	else if (_name == "Bishop")
	{
		piece = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	else if (_name == "Rook")
	{
		piece = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	else if (_name == "Queen")
	{
		piece = GetWorld()->SpawnActor<APiece_Queen>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	else if (_name == "King")
	{
		piece = GetWorld()->SpawnActor<APiece_King>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Piece: Invalid piece to spawn."));
	}

	if (piece != nullptr)
	{
		piece->SetSquareID(_squareID);
		m_board->m_squares[_squareID]->SetOccupiedPiece(piece);
		piece->SetActorLocation(m_board->m_squares[_squareID]->GetActorLocation() + FVector(0.0, 0.0, 10.0f));
		piece->SetID(_pieceID);
		if (!_promoting)
		{
			if (_isWhite)
			{
				m_whitePieces.push_back(piece);
			}
			else
			{
				piece->SetBlack();
				m_blackPieces.push_back(piece);
			}
		}
		else
		{
			if (_isWhite)
			{
				m_whitePieces[_pieceID] = piece;
			}
			else
			{
				piece->SetBlack();
				m_blackPieces[_pieceID] = piece;
			}
		}
		piece->SpawnBlueprint(m_board->m_squares[0]->GetDimensions(), _rot);
	}
}

void AGame_Controller::SpawnPieces()
{
	// WHITE PIECES
	for (int i = 0; i < 8; ++i)
	{
		SpawnPiece("Pawn", true, 8 + i, i, i, 1, {0.0f, 90.0f, 0.0f});
	}
	SpawnPiece("Rook", true, 7, 8, 7, 0, {0.0f, 90.0f, 0.0f});
	SpawnPiece("Rook", true, 0, 9, 0, 0, {0.0f, 90.0f, 0.0f});
	SpawnPiece("Knight", true, 6, 10, 6, 0, {0.0f, 90.0f, 0.0f});
	SpawnPiece("Knight", true, 1, 11, 1, 0, {0.0f, 90.0f, 0.0f});
	SpawnPiece("Bishop", true, 5, 12, 5, 0, {0.0f, 90.0f, 0.0f});
	SpawnPiece("Bishop", true, 2, 13, 2, 0, {0.0f, 90.0f, 0.0f});
	SpawnPiece("Queen", true, 4, 14, 4, 0, {0.0f, 90.0f, 0.0f});
	SpawnPiece("King", true, 3, 15, 3, 0, {0.0f, 90.0f, 0.0f});

	// BLACK PIECES
	for (int i = 0; i < 8; ++i)
	{
		SpawnPiece("Pawn", false, 48 + i, i, i, 6, {0.0f, -90.0f, 0.0f});
	}
	SpawnPiece("Rook", false, 63, 9, 7, 7, {0.0f, -90.0f, 0.0f});
	SpawnPiece("Rook", false, 56, 8, 0, 7, {0.0f, -90.0f, 0.0f});
	SpawnPiece("Knight", false, 62, 11, 6, 7, {0.0f, -90.0f, 0.0f});
	SpawnPiece("Knight", false, 57, 10, 1, 7, {0.0f, -90.0f, 0.0f});
	SpawnPiece("Bishop", false, 61, 13, 5, 7, {0.0f, -90.0f, 0.0f});
	SpawnPiece("Bishop", false, 58, 12, 2, 7, {0.0f, -90.0f, 0.0f});
	SpawnPiece("Queen", false, 60, 14, 4, 7, {0.0f, -90.0f, 0.0f});
	SpawnPiece("King", false, 59, 15, 3, 7, {0.0f, -90.0f, 0.0f});
}

void AGame_Controller::LeftMouseClick()
{
	bool bIsCharacterHit = false;
	bool enemyPieceSelected = false;

	// Deselect previous piece
	if (m_selectedPiece != nullptr)
	{
		m_selectedPiece->DeselectPiece();
		m_selectedPiece->GetCharacter()->SetActorEnableCollision(false);
	}

	// Get hit result
	GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, m_target);

	// Reenable collision
	if (m_selectedPiece != nullptr)
	{
		m_selectedPiece->GetCharacter()->SetActorEnableCollision(true);
	}

	// Return if nothing was hit
	if (m_target.GetActor() == nullptr)
	{
		UnhighlightMoves();
		m_selectedPiece = nullptr;
		return;
	}

	// Actor was hit
	UE_LOG(LogTemp, Warning, TEXT("Target: %s"), *FString(m_target.GetActor()->GetName()));
	// Check if hit was on character
	ACharacter *hitCharacter = Cast<ACharacter>(m_target.GetActor());
	bIsCharacterHit = hitCharacter != nullptr;
	// Character selected
	if (bIsCharacterHit)
	{
		m_targetPiece = Cast<APiece>(hitCharacter->GetOwner());
		UE_LOG(LogTemp, Warning, TEXT("BlueprintOwner: %s"), *m_targetPiece->GetName());

		// Handle Piece selection
		// Existing selection
		if (m_selectedPiece != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Prevous selection: %s"), *m_selectedPiece->GetName());
			enemyPieceSelected = m_selectedPiece->GetIsWhite() != m_targetPiece->GetIsWhite();
			// Try atack enemy piece
			if (enemyPieceSelected)
			{
				bool bIsValidMove = SelectSquare(enemyPieceSelected);
				UnhighlightMoves();
				if (bIsValidMove)
				{
					UE_LOG(LogTemp, Warning, TEXT("Valid attack move"));
					CheckForCheckmate();
					CheckForStalemate();
					// If pawn is being promoted, don't immediately set to nullptr...
					// ...piece needs to be destroyed first in PromotePawn()
					if (!m_promoting)
					{
						m_selectedPiece = nullptr;
					}
				}
			}
		}

		// Switch selection
		if (!enemyPieceSelected)
		{
			// Clear data from previously selected piece
			UnhighlightMoves();
			m_validMoves.clear();
			// Highlight piece and calculate moves
			SelectPiece();
		}
	}

	// Square selection
	else if (m_target.GetActor()->IsA(ABoard_Square::StaticClass()) || enemyPieceSelected)
	{
		// Move piece
		bool validMove = SelectSquare(enemyPieceSelected);
		UnhighlightMoves();

		if (validMove)
		{
			CheckForCheckmate();
			CheckForStalemate();
			// If pawn is being promoted, don't immediately set to nullptr...
			// ...piece needs to be destroyed first in PromotePawn()
			if (!m_promoting)
			{
				m_selectedPiece = nullptr;
			}
		}
		// If not valid move, set piece to nullptr anyway...
		// ... to allow user to re-select piece
		else
		{
			m_selectedPiece = nullptr;
		}
	}
}

void AGame_Controller::RightMouseClick()
{
	// Rotate camera
}

void AGame_Controller::ScrollUp()
{
	AGame_Player *m_camera = m_cameraOne;
	if (!m_whiteMove)
	{
		m_camera = m_cameraTwo;
	}
	if (m_camera->GetSpringArmLength() > 100.0f)
	{
		m_camera->SetSpringArmLength(-10.0f);
	}
}

void AGame_Controller::ScrollDown()
{
	AGame_Player *m_camera = m_cameraOne;
	if (!m_whiteMove)
	{
		m_camera = m_cameraTwo;
	}
	if (m_camera->GetSpringArmLength() < 400.0f)
	{
		m_camera->SetSpringArmLength(10.0f);
	}
}

void AGame_Controller::SelectPiece()
{
	m_selectedPiece = m_targetPiece;

	// Player can only select their own pieces
	if ((m_selectedPiece->GetIsWhite() && m_whiteMove) || (!m_selectedPiece->GetIsWhite() && !m_whiteMove))
	{
		// Calculate available moves
		m_selectedPiece->SelectPiece();
		m_availableMovesCopy = m_selectedPiece->CalculateMoves();
		m_filteredMoves = FilterRealMoves(m_selectedPiece, m_availableMovesCopy);

		// Castling
		if (m_selectedPiece->IsA(APiece_King::StaticClass()))
		{
			if (m_whiteMove)
			{
				if (!m_whiteCheck)
				{
					// King is yet to make a move
					if (m_selectedPiece->GetFirstMove())
					{
						if (m_whiteKingSideCastle)
						{
							CalculateCastleKingSide(0, 1, 2, m_blackAttacking);
						}
						if (m_whiteQueenSideCastle)
						{
							CalculateCastleQueenSide(7, 6, 5, 4, m_blackAttacking);
						}
					}
					else
					{
						m_whiteKingSideCastle = false;
						m_whiteQueenSideCastle = false;
					}
				}
			}
			else
			{
				if (!m_blackCheck)
				{
					// King is yet to make a move
					if (m_selectedPiece->GetFirstMove())
					{
						if (m_blackKingSideCastle)
						{
							CalculateCastleKingSide(56, 57, 58, m_whiteAttacking);
						}
						if (m_blackQueenSideCastle)
						{
							CalculateCastleQueenSide(63, 62, 61, 60, m_whiteAttacking);
						}
					}
					else
					{
						m_blackKingSideCastle = false;
						m_blackQueenSideCastle = false;
					}
				}
			}
		}

		for (int i = 0; i < m_filteredMoves.size(); ++i)
		{
			SimulateMove(m_selectedPiece, i);
		}

		if (m_selectedPiece->IsA(APiece_Pawn::StaticClass()))
		{
			EnPassant();
		}

		HighlightMoves();

		// Re-calculate opponents attacking moves to keep as reference for castling
		CalculateAttackingMoves(!m_whiteMove);
	}
	else
	{
		m_selectedPiece = nullptr;
	}
}

bool AGame_Controller::SelectSquare(bool _enemyPieceSelected)
{
	if (m_movesHighlighted)
	{
		if (_enemyPieceSelected)
		{
			int square = m_targetPiece->GetSquareID();
			m_selectedSquare = m_board->m_squares[square];
		}
		else
		{
			m_selectedSquare = Cast<ABoard_Square>(m_target.GetActor());
		}
		for (int i = 0; i < m_validMoves.size(); ++i)
		{
			bool takenSound = false;
			// Check if selected square is an available move
			if (m_validMoves[i] == m_selectedSquare->GetID())
			{
				// TAKING PIECE
				if (m_selectedSquare->GetOccupied())
				{
					PlayPieceTaken(m_selectedSquare->GetOccupiedPiece()->GetID(), m_selectedSquare->GetOccupiedPiece()->GetIsWhite());
					takenSound = true;
					// Remove piece from active pieces
					if (m_selectedSquare->GetOccupiedPiece()->GetIsWhite())
					{
						m_whitePieces[m_selectedSquare->GetOccupiedPiece()->GetID()] = nullptr;
					}
					else
					{
						m_blackPieces[m_selectedSquare->GetOccupiedPiece()->GetID()] = nullptr;
					}
					// Kill piece
					m_selectedSquare->GetOccupiedPiece()->m_spawnedBlueprint->Destroy();
					m_selectedSquare->GetOccupiedPiece()->Destroy();
				}

				// CASTLING
				bool castling = false;
				if (m_selectedPiece->IsA(APiece_King::StaticClass()))
				{
					if (m_whiteMove)
					{
						if (m_selectedSquare->GetID() == 1 && m_whiteKingSideCastle)
						{
							// Castle King side
							Castle(0, 2);
							castling = true;
							m_whiteKingSideCastle = false;
						}
						else if (m_selectedSquare->GetID() == 5 && m_whiteQueenSideCastle)
						{
							// Castle Queen side
							Castle(7, 4);
							castling = true;
							m_whiteQueenSideCastle = false;
						}
					}
					else
					{
						if (m_selectedSquare->GetID() == 57 && m_blackKingSideCastle)
						{
							// Castle King side
							Castle(56, 58);
							castling = true;
							m_blackKingSideCastle = false;
						}
						else if (m_selectedSquare->GetID() == 61 && m_blackQueenSideCastle)
						{
							// Castle Queen side
							Castle(63, 60);
							castling = true;
							m_blackQueenSideCastle = false;
						}
					}
					m_enPassant = false;
					m_enPassantVictim = nullptr;
				}

				// EN PASSANT
				if (m_enPassant)
				{
					// Clicked En Passant square (unoccupied diagonal square)
					if (!m_selectedSquare->GetOccupied() && abs(m_selectedPiece->GetSquareID() - m_selectedSquare->GetID() != 8))
					{
						int enemySquare;
						if (m_whiteMove)
						{
							enemySquare = m_selectedSquare->GetID() - 8;
						}
						else
						{
							enemySquare = m_selectedSquare->GetID() + 8;
						}
						PlayPieceTaken(m_board->m_squares[enemySquare]->GetOccupiedPiece()->GetID(), m_board->m_squares[enemySquare]->GetOccupiedPiece()->GetIsWhite());
						m_blackPieces[m_board->m_squares[enemySquare]->GetOccupiedPiece()->GetID()] = nullptr;
						m_board->m_squares[enemySquare]->GetOccupiedPiece()->m_spawnedBlueprint->Destroy();
						m_board->m_squares[enemySquare]->GetOccupiedPiece()->Destroy();
						m_board->m_squares[enemySquare]->RemoveOccupiedPiece();
						m_enPassant = false;
						m_enPassantVictim = nullptr;
					}
				}

				// NORMAL MOVE
				if (!castling)
				{
					// Set En Passant victim
					if (m_selectedPiece->IsA(APiece_Pawn::StaticClass()) && abs(m_selectedPiece->GetSquareID() - m_selectedSquare->GetID()) == 16)
					{
						m_enPassantVictim = m_selectedPiece;
					}
					else
					{
						m_enPassant = false;
						m_enPassantVictim = nullptr;
					}

					// Unoccupy previous square
					m_board->m_squares[m_selectedPiece->GetSquareID()]->RemoveOccupiedPiece();

					// Move piece and assign to new square
					m_selectedPiece->MovePiece(m_selectedSquare->GetID(), m_selectedSquare->GetDimensions());

					// Occupy new square with moved piece
					m_board->m_squares[m_selectedSquare->GetID()]->SetOccupiedPiece(m_selectedPiece);
				}

				// PAWN PROMOTION
				if (m_selectedPiece->IsA(APiece_Pawn::StaticClass()))
				{
					// White pawn reached end of board
					if (m_selectedPiece->GetIsWhite() && m_selectedPiece->GetSquareID() > 55)
					{
						m_promoting = true;
						PromotedPieceUI(m_selectedPiece->GetIsWhite());
					}
					// Black pawn reached end of board
					else if (!m_selectedPiece->GetIsWhite() && m_selectedPiece->GetSquareID() < 8)
					{
						m_promoting = true;
						PromotedPieceUI(m_selectedPiece->GetIsWhite());
					}
				}

				// Calculate if move has caused check on opponent, then change turns
				if (m_whiteMove)
				{
					std::vector<int> attackedSquares = CalculateAttackingMoves(true);
					if (CheckKingAttack(true, attackedSquares))
					{
						m_blackCheck = true;
						UE_LOG(LogTemp, Warning, TEXT("Black in check."));
						PlayCheckSound();
					}
					m_whiteMove = false;
					//SetViewTargetWithBlend(m_cameraTwo, m_blendTime);
				}
				else
				{
					std::vector<int> attackedSquares = CalculateAttackingMoves(false);
					if (CheckKingAttack(false, attackedSquares))
					{
						m_whiteCheck = true;
						UE_LOG(LogTemp, Warning, TEXT("White in check."));
						PlayCheckSound();
					}
					m_whiteMove = true;
					//SetViewTargetWithBlend(m_cameraOne, m_blendTime);
				}
				if (!m_whiteCheck && !m_blackCheck && !takenSound)
				{
					PlayMovePieceSound();
				}
				return true;
			}
		}
	}
	return false;
}

void AGame_Controller::HighlightMoves()
{
	if (m_validMoves.size() > 0)
	{
		m_movesHighlighted = true;
		for (int i = 0; i < m_validMoves.size(); ++i)
		{
			if (m_board->m_squares[m_validMoves[i]]->GetOccupied())
			{
				m_board->SetEnemyMaterial(m_validMoves[i]);
			}
			else
			{
				m_board->SetSelectedMaterial(m_validMoves[i]);
			}
		}
	}
}

void AGame_Controller::UnhighlightMoves()
{
	for (int i = 0; i < m_validMoves.size(); ++i)
	{
		m_board->ResetMaterial(m_validMoves[i]);
	}
	m_movesHighlighted = false;
}

std::vector<int> AGame_Controller::CalculateAttackingMoves(bool _isWhite)
{
	// Clear previously attacked squares
	m_whiteAttacking.clear();
	m_blackAttacking.clear();

	std::vector<APiece *> attackingPieces;
	std::vector<int> attackedSquares;

	if (_isWhite)
	{
		attackingPieces = m_whitePieces;
	}
	else
	{
		attackingPieces = m_blackPieces;
	}

	// Calculate moves for each active piece
	if (attackingPieces.size() > 0)
	{
		for (int i = 0; i < attackingPieces.size(); ++i)
		{
			if (attackingPieces[i] != nullptr)
			{
				std::vector<std::vector<int>> unfilteredMoves = attackingPieces[i]->CalculateMoves();

				// Remove pawn forward moves (not attacking moves)
				if (attackingPieces[i]->IsA(APiece_Pawn::StaticClass()))
				{
					unfilteredMoves[1].clear();
				}
				std::vector<int> filteredMoves = FilterSimulatedMoves(unfilteredMoves, _isWhite);

				for (int j = 0; j < filteredMoves.size(); ++j)
				{
					attackedSquares.push_back(filteredMoves[j]);
				}
			}
		}
	}
	// Erase overlaps (two pieces attacking the same square)
	sort(attackedSquares.begin(), attackedSquares.end());
	attackedSquares.erase(std::unique(attackedSquares.begin(), attackedSquares.end()), attackedSquares.end());
	if (_isWhite)
	{
		m_whiteAttacking = attackedSquares;
	}
	else
	{
		m_blackAttacking = attackedSquares;
	}
	return attackedSquares;
}

bool AGame_Controller::CheckKingAttack(bool _isWhite, std::vector<int> _attackedSquares)
{
	for (int k = 0; k < _attackedSquares.size(); ++k)
	{
		if (m_board->m_squares[_attackedSquares[k]]->GetOccupied())
		{
			if (m_board->m_squares[_attackedSquares[k]]->GetOccupiedPiece()->IsA(APiece_King::StaticClass()))
			{
				if (!_isWhite)
				{
					if (m_board->m_squares[_attackedSquares[k]]->GetOccupiedPiece()->GetIsWhite())
					{
						return true;
					}
				}
				else
				{
					if (!m_board->m_squares[_attackedSquares[k]]->GetOccupiedPiece()->GetIsWhite())
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

void AGame_Controller::SimulateMove(APiece *_piece, int _move)
{
	// SIMULATE MOVE:
	//	-	Validate which moves are legal (aren't going to cause check on self)

	// Store temp data
	int currentSquare = _piece->GetSquareID();
	int newSquare = m_filteredMoves[_move];
	APiece *newSquarePiece = nullptr;
	bool replace = false;

	// If new square is occupied
	if (m_board->m_squares[m_filteredMoves[_move]]->GetOccupied())
	{
		// Store piece
		newSquarePiece = m_board->m_squares[m_filteredMoves[_move]]->GetOccupiedPiece();
		// Remove piece from square
		m_board->m_squares[m_filteredMoves[_move]]->RemoveOccupiedPiece();
		// Remove piece from active pieces
		if (m_whiteMove)
		{
			m_blackPieces[newSquarePiece->GetID()] = nullptr;
		}
		else
		{
			m_whitePieces[newSquarePiece->GetID()] = nullptr;
		}
		// Mark true to ensure the piece is put back
		replace = true;
	}

	// Remove selected piece from current square
	m_board->m_squares[currentSquare]->RemoveOccupiedPiece();
	// Move selected piece
	_piece->SetSquareID(m_filteredMoves[_move]);
	// Occupy new square with piece
	m_board->m_squares[m_filteredMoves[_move]]->SetOccupiedPiece(_piece);
	// Check if this move is valid (won't put yourself in check)
	if (!CheckSelfForCheck())
	{
		// Move is valid
		m_validMoves.push_back(m_filteredMoves[_move]);
	}
	// Remove selected piece from new square
	m_board->m_squares[m_filteredMoves[_move]]->RemoveOccupiedPiece();

	if (replace)
	{
		// Put back original new square piece
		m_board->m_squares[m_filteredMoves[_move]]->SetOccupiedPiece(newSquarePiece);
		//  Add piece back to active pieces
		if (m_whiteMove)
		{
			m_blackPieces[newSquarePiece->GetID()] = newSquarePiece;
		}
		else
		{
			m_whitePieces[newSquarePiece->GetID()] = newSquarePiece;
		}
	}
	// Move selected piece back to its current square
	_piece->SetSquareID(currentSquare);
	// Occupy current square with piece
	m_board->m_squares[currentSquare]->SetOccupiedPiece(_piece);
}

std::vector<int> AGame_Controller::FilterSimulatedMoves(std::vector<std::vector<int>> _unfilteredMoves, bool _isWhite)
{
	std::vector<int> moves;

	for (int i = 0; i < _unfilteredMoves.size(); ++i)
	{
		for (int j = 0; j < _unfilteredMoves[i].size(); ++j)
		{
			if (m_board->m_squares[_unfilteredMoves[i][j]]->GetOccupied())
			{
				// Simulating whites move (calculating blacks attacking squares)
				if (!_isWhite)
				{
					// Square occupied by a black piece
					if (!m_board->m_squares[_unfilteredMoves[i][j]]->GetOccupiedPiece()->GetIsWhite())
					{
						break;
					}
					// Square occupied by a white piece
					else
					{
						moves.push_back(_unfilteredMoves[i][j]);
						break;
					}
				}
				// Simulating blacks move (calculating whites attacking squares)
				else
				{
					// Square occupied by a black piece
					if (!m_board->m_squares[_unfilteredMoves[i][j]]->GetOccupiedPiece()->GetIsWhite())
					{
						moves.push_back(_unfilteredMoves[i][j]);
						break;
					}
					// Square occupied by a white piece
					else
					{
						break;
					}
				}
			}
			// Not occupied
			else
			{
				moves.push_back(_unfilteredMoves[i][j]);
			}
		}
	}
	return moves;
}

std::vector<int> AGame_Controller::FilterRealMoves(APiece *_piece, std::vector<std::vector<int>> _movesToFilter)
{
	std::vector<int> filteredMoves;

	// Loop moves
	for (int i = 0; i < _movesToFilter.size(); ++i)
	{
		for (int j = 0; j < _movesToFilter[i].size(); ++j)
		{
			// PAWN UNIQUE CASE
			if (_piece->IsA(APiece_Pawn::StaticClass()))
			{
				// Diagonal move
				if (i == 0 || i == 2)
				{
					if (m_board->m_squares[_movesToFilter[i][j]]->GetOccupied())
					{
						// White piece selected
						if (_piece->GetIsWhite())
						{
							// Square occupied by a black piece
							if (!m_board->m_squares[_movesToFilter[i][j]]->GetOccupiedPiece()->GetIsWhite())
							{
								filteredMoves.push_back(_movesToFilter[i][j]);
							}
						}
						// Black piece selected
						else
						{
							// Square occupied by a white piece
							if (m_board->m_squares[_movesToFilter[i][j]]->GetOccupiedPiece()->GetIsWhite())
							{
								filteredMoves.push_back(_movesToFilter[i][j]);
							}
						}
					}
				}
				// Forward move
				else
				{
					if (m_board->m_squares[_movesToFilter[i][j]]->GetOccupied())
					{
						break;
					}
					// Not occupied
					else
					{
						filteredMoves.push_back(_movesToFilter[i][j]);
					}
				}
			}
			// ALL OTHER PIECES
			else
			{
				if (m_board->m_squares[_movesToFilter[i][j]]->GetOccupied())
				{
					// White piece selected
					if (_piece->GetIsWhite())
					{
						// Square occupied by a black piece
						if (!m_board->m_squares[_movesToFilter[i][j]]->GetOccupiedPiece()->GetIsWhite())
						{
							filteredMoves.push_back(_movesToFilter[i][j]);
						}
						break;
					}
					// Black piece selected
					else
					{
						// Square occupied by a white piece
						if (m_board->m_squares[_movesToFilter[i][j]]->GetOccupiedPiece()->GetIsWhite())
						{
							filteredMoves.push_back(_movesToFilter[i][j]);
						}
						break;
					}
				}
				// Not occupied
				else
				{
					filteredMoves.push_back(_movesToFilter[i][j]);
				}
			}
		}
	}
	return filteredMoves;
}

bool AGame_Controller::CheckSelfForCheck()
{
	// Simulate whites move
	if (m_whiteMove)
	{
		std::vector<int> attackedSquares = CalculateAttackingMoves(false);
		return CheckKingAttack(false, attackedSquares);
	}
	// Simulate blacks move
	else
	{
		std::vector<int> attackedSquares = CalculateAttackingMoves(true);
		return CheckKingAttack(true, attackedSquares);
	}
	// Valid move (won't cause check on self)
	return false;
}

void AGame_Controller::MoveOutOfCheck(std::vector<APiece *> _pieces)
{
	for (int i = 0; i < _pieces.size(); ++i)
	{
		if (_pieces[i] != nullptr)
		{
			APiece *piece = _pieces[i];
			std::vector<std::vector<int>> moves = piece->CalculateMoves();
			// Filter the moves
			m_filteredMoves = FilterRealMoves(_pieces[i], moves);
			// Simulate the filtered moves
			for (int j = 0; j < m_filteredMoves.size(); ++j)
			{
				SimulateMove(piece, j);
			}
		}
	}
}

void AGame_Controller::CheckForCheckmate()
{
	m_validMoves.clear();

	// White move and white in check
	if (m_whiteMove && m_whiteCheck)
	{
		MoveOutOfCheck(m_whitePieces);
		if (m_validMoves.size() <= 0)
		{
			m_gameOver = true;
			// Call from blueprint
			BlackWin();
		}
		else
		{
			m_whiteCheck = false;
		}
	}
	// Black move and black in check
	else if (!m_whiteMove && m_blackCheck)
	{
		MoveOutOfCheck(m_blackPieces);
		if (m_validMoves.size() <= 0)
		{
			m_gameOver = true;
			// Call from blueprint
			WhiteWin();
		}
		else
		{
			m_blackCheck = false;
		}
	}
}

void AGame_Controller::CheckForStalemate()
{
	m_validMoves.clear();

	APiece *piece;
	std::vector<APiece *> pieces;

	if (m_whiteMove)
	{
		pieces = m_whitePieces;
	}
	else
	{
		pieces = m_blackPieces;
	}

	for (int i = 0; i < pieces.size(); ++i)
	{
		if (pieces[i] == nullptr)
		{
			continue;
		}
		piece = pieces[i];
		m_availableMovesCopy = piece->CalculateMoves();
		m_filteredMoves = FilterRealMoves(piece, m_availableMovesCopy);

		// Castling
		if (piece->IsA(APiece_King::StaticClass()))
		{
			if (m_whiteMove)
			{
				if (!m_whiteCheck)
				{
					// King is yet to make a move
					if (piece->GetFirstMove())
					{
						if (m_whiteKingSideCastle)
						{
							CalculateCastleKingSide(0, 1, 2, m_blackAttacking);
						}
						if (m_whiteQueenSideCastle)
						{
							CalculateCastleQueenSide(7, 6, 5, 4, m_blackAttacking);
						}
					}
					else
					{
						m_whiteKingSideCastle = false;
						m_whiteQueenSideCastle = false;
					}
				}
			}
			else
			{
				if (!m_blackCheck)
				{
					// King is yet to make a move
					if (piece->GetFirstMove())
					{
						if (m_blackKingSideCastle)
						{
							CalculateCastleKingSide(56, 57, 58, m_whiteAttacking);
						}
						if (m_blackQueenSideCastle)
						{
							CalculateCastleQueenSide(63, 62, 61, 60, m_whiteAttacking);
						}
					}
					else
					{
						m_blackKingSideCastle = false;
						m_blackQueenSideCastle = false;
					}
				}
			}
		}

		for (int j = 0; j < m_filteredMoves.size(); ++j)
		{
			SimulateMove(piece, j);
		}

		if (piece->IsA(APiece_Pawn::StaticClass()))
		{
			EnPassant();
		}

		for (int k = 0; k < m_validMoves.size(); ++k)
		{
			UE_LOG(LogTemp, Warning, TEXT("Move: %d"), m_validMoves[k]);
		}

		if (m_validMoves.size() > 0)
		{
			return;
		}
	}
	if (!m_gameOver)
	{
		Stalemate();
	}
}

int AGame_Controller::PromotePawn(int _pieceID)
{
	// Retain data
	int pieceID = m_selectedPiece->GetID();
	int squareID = m_selectedPiece->GetSquareID();
	bool isWhite = m_selectedPiece->GetIsWhite();

	// Destroy old piece
	m_selectedPiece->m_spawnedBlueprint->Destroy();
	m_selectedPiece->Destroy();

	int xPos = squareID % 8;
	int yPos = squareID / 8;
	std::string name;
	FRotator rot = {0.0f, 90.0f, 0.0f};

	if (m_whiteMove)
	{
		rot = {0.0f, -90.0f, 0.0f};
	}

	if (_pieceID == 1)
	{
		name = "Knight";
	}
	else if (_pieceID == 2)
	{
		name = "Bishop";
	}
	else if (_pieceID == 3)
	{
		name = "Rook";
	}
	else if (_pieceID == 4)
	{
		name = "Queen";
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid piece ID for pawn promotion!"));
	}

	SpawnPiece(name, !m_whiteMove, squareID, pieceID, xPos, yPos, rot, true);

	m_selectedPiece = nullptr;
	m_promoting = false;
	return pieceID;
}

void AGame_Controller::CalculateCastleKingSide(int _rookPos, int _knightPos, int _bishopPos, std::vector<int> &_opponentAttacking)
{
	// Check if rook is even their
	if (m_board->m_squares[_rookPos]->GetOccupied() && m_board->m_squares[_rookPos]->GetOccupiedPiece()->IsA(APiece_Rook::StaticClass()))
	{
		// Rook is yet to make a move
		if (m_board->m_squares[_rookPos]->GetOccupiedPiece()->GetFirstMove())
		{
			// Knight and Bishop are absent
			if (!m_board->m_squares[_knightPos]->GetOccupied() && !m_board->m_squares[_bishopPos]->GetOccupied())
			{
				// Check absent squares aren't being attacked
				for (int i = 0; i < _opponentAttacking.size(); ++i)
				{
					if (_opponentAttacking[i] == _knightPos || _opponentAttacking[i] == _bishopPos)
					{
						return;
					}
				}
				m_validMoves.push_back(_knightPos);
			}
		}
	}
}

void AGame_Controller::CalculateCastleQueenSide(int _rookPos, int _knightPos, int _bishopPos, int _queenPos, std::vector<int> &_opponentAttacking)
{
	// Check if rook is even their
	if (m_board->m_squares[_rookPos]->GetOccupied() && m_board->m_squares[_rookPos]->GetOccupiedPiece()->IsA(APiece_Rook::StaticClass()))
	{
		// Rook is yet to make a move
		if (m_board->m_squares[_rookPos]->GetOccupiedPiece()->GetFirstMove())
		{
			// Knight, Bishop and Queen are absent
			if (!m_board->m_squares[_knightPos]->GetOccupied() && !m_board->m_squares[_bishopPos]->GetOccupied() && !m_board->m_squares[_queenPos]->GetOccupied())
			{
				// Check absent squares aren't being attacked
				for (int i = 0; i < _opponentAttacking.size(); ++i)
				{
					if (_opponentAttacking[i] == _knightPos || _opponentAttacking[i] == _bishopPos || _opponentAttacking[i] == _queenPos)
					{
						return;
					}
				}
				m_validMoves.push_back(_bishopPos);
			}
		}
	}
}

void AGame_Controller::Castle(int _rookPos, int _rookTarget)
{
	// KING
	// Unoccupy previous square
	m_board->m_squares[m_selectedPiece->GetSquareID()]->RemoveOccupiedPiece();
	// Move piece and assign to new square
	m_selectedPiece->MovePiece(m_selectedSquare->GetID(), m_selectedSquare->GetDimensions());
	// Occupy new square with moved piece
	m_board->m_squares[m_selectedSquare->GetID()]->SetOccupiedPiece(m_selectedPiece);

	// ROOK
	APiece *rook = m_board->m_squares[_rookPos]->GetOccupiedPiece();
	// Unoccupy previous square
	m_board->m_squares[_rookPos]->RemoveOccupiedPiece();
	// Move piece and assign to new square
	rook->MovePiece(_rookTarget, m_selectedSquare->GetDimensions());
	// Occupy new square with moved piece
	m_board->m_squares[_rookTarget]->SetOccupiedPiece(rook);
}

void AGame_Controller::EnPassant()
{
	int currentSquare = m_selectedPiece->GetSquareID();
	if (m_selectedPiece->GetSquareID() % 8 != 7) // Not left side of board
	{
		if (m_board->m_squares[currentSquare + 1]->GetOccupied()) // Square to left
		{
			if (m_board->m_squares[currentSquare + 1]->GetOccupiedPiece() == m_enPassantVictim)
			{
				if (m_whiteMove)
				{
					m_validMoves.push_back(currentSquare + 9);
				}
				else
				{
					m_validMoves.push_back(currentSquare - 7);
				}
				m_enPassant = true;
			}
		}
	}
	if (m_selectedPiece->GetSquareID() % 8 != 0) // Not right side of board
	{
		if (m_board->m_squares[currentSquare - 1]->GetOccupied()) // Square to right
		{
			if (m_board->m_squares[currentSquare - 1]->GetOccupiedPiece() == m_enPassantVictim)
			{
				if (m_whiteMove)
				{
					m_validMoves.push_back(currentSquare + 7);
				}
				else
				{
					m_validMoves.push_back(currentSquare - 9);
				}
				m_enPassant = true;
			}
		}
	}
}