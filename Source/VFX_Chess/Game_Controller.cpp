// Fill out your copyright notice in the Description page of Project Settings.


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
	DefaultMouseCursor = EMouseCursor::Hand;
}

// Called when the game starts or when spawned
void AGame_Controller::BeginPlay()
{
	Super::BeginPlay();

	// Spawn board
	m_board = GetWorld()->SpawnActor<ABoard>(FVector::ZeroVector, FRotator::ZeroRotator);

	// Spawn players
	m_playerOne = GetWorld()->SpawnActor<AGame_Player>(FVector(350.0f, 50.0f, 550.0f), FRotator(0, 90.0f, 0));
	m_playerTwo = GetWorld()->SpawnActor<AGame_Player>(FVector(350.0f, -650.0f, 550.0f), FRotator(0, -90.0f, 0));
	m_playerTwo->SetIsWhite(false);
	Possess(m_playerOne);

	SpawnPieces();
}

void AGame_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Setup inputs
	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AGame_Controller::LeftMouseClick);
}

// Called every frame
void AGame_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGame_Controller::SpawnPieces()
{
	// WHITE PIECES
	for (int i = 0; i < 8; ++i)
	{
		APiece_Pawn* whitePawn = GetWorld()->SpawnActor<APiece_Pawn>(FVector::ZeroVector, FRotator::ZeroRotator);
		whitePawn->SetActorLocation({ m_board->m_squares[i]->GetDimensions().X * i, m_board->m_squares[i]->GetDimensions().Y, whitePawn->GetDimensions().Z });
		whitePawn->SetSquare(i + 8);
		m_board->m_squares[i + 8]->SetOccupiedPiece(whitePawn);
		whitePawn->SetID(i);
		m_whitePieces.push_back(whitePawn);
	}

	APiece_Rook* whiteRook_1 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteRook_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 7, 0, whiteRook_1->GetDimensions().Z });
	whiteRook_1->SetSquare(7);
	m_board->m_squares[7]->SetOccupiedPiece(whiteRook_1);
	whiteRook_1->SetID(8);
	m_whitePieces.push_back(whiteRook_1);

	APiece_Rook* whiteRook_2 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteRook_2->SetActorLocation({ 0, 0, whiteRook_2->GetDimensions().Z });
	whiteRook_2->SetSquare(0);
	m_board->m_squares[0]->SetOccupiedPiece(whiteRook_2);
	whiteRook_2->SetID(9);
	m_whitePieces.push_back(whiteRook_2);

	APiece_Knight* whiteKnight_1 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteKnight_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 6, 0, whiteKnight_1->GetDimensions().Z });
	whiteKnight_1->SetSquare(6);
	m_board->m_squares[6]->SetOccupiedPiece(whiteKnight_1);
	whiteKnight_1->SetID(10);
	m_whitePieces.push_back(whiteKnight_1);

	APiece_Knight* whiteKnight_2 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteKnight_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X, 0, whiteKnight_2->GetDimensions().Z });
	whiteKnight_2->SetSquare(1);
	m_board->m_squares[1]->SetOccupiedPiece(whiteKnight_2);
	whiteKnight_2->SetID(11);
	m_whitePieces.push_back(whiteKnight_2);

	APiece_Bishop* whiteBishop_1 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteBishop_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 5, 0, whiteBishop_1->GetDimensions().Z });
	whiteBishop_1->SetSquare(5);
	m_board->m_squares[5]->SetOccupiedPiece(whiteBishop_1);
	whiteBishop_1->SetID(12);
	m_whitePieces.push_back(whiteBishop_1);

	APiece_Bishop* whiteBishop_2 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteBishop_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 2, 0, whiteBishop_2->GetDimensions().Z });
	whiteBishop_2->SetSquare(2);
	m_board->m_squares[2]->SetOccupiedPiece(whiteBishop_2);
	whiteBishop_2->SetID(13);
	m_whitePieces.push_back(whiteBishop_2);

	APiece_Queen* whiteQueen = GetWorld()->SpawnActor<APiece_Queen>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteQueen->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 4, 0, whiteQueen->GetDimensions().Z });
	whiteQueen->SetSquare(4);
	m_board->m_squares[4]->SetOccupiedPiece(whiteQueen);
	whiteQueen->SetID(14);
	m_whitePieces.push_back(whiteQueen);

	APiece_King* whiteKing = GetWorld()->SpawnActor<APiece_King>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteKing->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 3, 0, whiteKing->GetDimensions().Z });
	whiteKing->SetSquare(3);
	m_board->m_squares[3]->SetOccupiedPiece(whiteKing);
	whiteKing->SetID(15);
	m_whitePieces.push_back(whiteKing);

	// BLACK PIECES
	for (int i = 0; i < 8; ++i)
	{
		APiece_Pawn* blackPawn = GetWorld()->SpawnActor<APiece_Pawn>(FVector::ZeroVector, FRotator::ZeroRotator);
		blackPawn->SetActorLocation({ m_board->m_squares[i]->GetDimensions().X * i, m_board->m_squares[i]->GetDimensions().Y * 6, blackPawn->GetDimensions().Z });
		blackPawn->SetBlack();
		blackPawn->SetSquare(i + 48);
		m_board->m_squares[i + 48]->SetOccupiedPiece(blackPawn);
		blackPawn->SetID(i);
		m_blackPieces.push_back(blackPawn);
	}

	APiece_Rook* blackRook_1 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackRook_1->SetActorLocation({ 0, m_board->m_squares[0]->GetDimensions().Y * 7, blackRook_1->GetDimensions().Z });
	blackRook_1->SetBlack();
	blackRook_1->SetSquare(56);
	m_board->m_squares[56]->SetOccupiedPiece(blackRook_1);
	blackRook_1->SetID(8);
	m_blackPieces.push_back(blackRook_1);

	APiece_Rook* blackRook_2 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackRook_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 7, m_board->m_squares[0]->GetDimensions().Y * 7, blackRook_2->GetDimensions().Z });
	blackRook_2->SetBlack();
	blackRook_2->SetSquare(63);
	m_board->m_squares[63]->SetOccupiedPiece(blackRook_2);
	blackRook_2->SetID(9);
	m_blackPieces.push_back(blackRook_2);

	APiece_Knight* blackKnight_1 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackKnight_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X, m_board->m_squares[0]->GetDimensions().Y * 7, blackKnight_1->GetDimensions().Z });
	blackKnight_1->SetBlack();
	blackKnight_1->SetSquare(57);
	m_board->m_squares[57]->SetOccupiedPiece(blackKnight_1);
	blackKnight_1->SetID(10);
	m_blackPieces.push_back(blackKnight_1);

	APiece_Knight* blackKnight_2 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackKnight_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 6, m_board->m_squares[0]->GetDimensions().Y * 7, blackKnight_2->GetDimensions().Z });
	blackKnight_2->SetBlack();
	blackKnight_2->SetSquare(62);
	m_board->m_squares[62]->SetOccupiedPiece(blackKnight_2);
	blackKnight_2->SetID(11);
	m_blackPieces.push_back(blackKnight_2);

	APiece_Bishop* blackBishop_1 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackBishop_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 2, m_board->m_squares[0]->GetDimensions().Y * 7, blackBishop_1->GetDimensions().Z });
	blackBishop_1->SetBlack();
	blackBishop_1->SetSquare(58);
	m_board->m_squares[58]->SetOccupiedPiece(blackBishop_1);
	blackBishop_1->SetID(12);
	m_blackPieces.push_back(blackBishop_1);

	APiece_Bishop* blackBishop_2 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackBishop_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 5, m_board->m_squares[0]->GetDimensions().Y * 7, blackBishop_2->GetDimensions().Z });
	blackBishop_2->SetBlack();
	blackBishop_2->SetSquare(61);
	m_board->m_squares[61]->SetOccupiedPiece(blackBishop_2);
	blackBishop_2->SetID(13);
	m_blackPieces.push_back(blackBishop_2);

	APiece_Queen* blackQueen = GetWorld()->SpawnActor<APiece_Queen>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackQueen->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 4, m_board->m_squares[0]->GetDimensions().Y * 7, blackQueen->GetDimensions().Z });
	blackQueen->SetBlack();
	blackQueen->SetSquare(60);
	m_board->m_squares[60]->SetOccupiedPiece(blackQueen);
	blackQueen->SetID(14);
	m_blackPieces.push_back(blackQueen);

	APiece_King* blackKing = GetWorld()->SpawnActor<APiece_King>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackKing->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 3, m_board->m_squares[0]->GetDimensions().Y * 7, blackKing->GetDimensions().Z });
	blackKing->SetBlack();
	blackKing->SetSquare(59);
	m_board->m_squares[59]->SetOccupiedPiece(blackKing);
	blackKing->SetID(15);
	m_blackPieces.push_back(blackKing);
}

void AGame_Controller::LeftMouseClick()
{
	// Deselect previous piece
	if (this->m_selectedPiece != nullptr)
	{
		this->m_selectedPiece->DeselectPiece();
	}

	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, m_target);

	if (m_target.GetActor() != nullptr)
	{
		// Piece selected
		if (m_target.GetActor()->IsA(APiece::StaticClass()))
		{
			// Clear data from previously selected piece
			UnhighlightMoves();
			m_filteredMoves.clear();
			m_validMoves.clear();
			// Highlight piece and calculate moves
			SelectPiece();
		}
		// Square selected
		else if (m_target.GetActor()->IsA(ABoard_Square::StaticClass()))
		{
			// Move piece
			SelectSquare();
			UnhighlightMoves();
			CheckForCheckmate();
		}
	}
	else
	{
		UnhighlightMoves();
	}
}

void AGame_Controller::SelectPiece()
{
	m_selectedPiece = Cast<APiece>(m_target.GetActor());
	
	// Player can only select their own pieces
	if ((m_selectedPiece->GetIsWhite() && m_whiteMove) || (!m_selectedPiece->GetIsWhite() && !m_whiteMove))
	{
		// Calculate available moves
		m_selectedPiece->SelectPiece();
		m_availableMovesCopy = m_selectedPiece->CalculateMoves();
		m_filteredMoves = FilterRealMoves(m_selectedPiece, m_availableMovesCopy);

		for (int i = 0; i < m_filteredMoves.size(); ++i)
		{
			SimulateMove(m_selectedPiece, i);
		}
		HighlightMoves();
	}
}

void AGame_Controller::SelectSquare()
{
	if (m_movesHighlighted)
	{
		m_selectedSquare = Cast<ABoard_Square>(m_target.GetActor());
		for (int i = 0; i < m_validMoves.size(); ++i)
		{
			// Check if selected square is an available move
			if (m_validMoves[i] == m_selectedSquare->GetID())
			{
				if (m_selectedSquare->GetOccupied())
				{
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
					m_selectedSquare->GetOccupiedPiece()->Destroy();
				}
				// Unoccupy previous square
				m_board->m_squares[m_selectedPiece->GetSquare()]->RemoveOccupiedPiece();

				// Move piece and assign to new square
				m_selectedPiece->MovePiece(m_selectedSquare->GetID(), m_selectedSquare->GetDimensions());

				// Occupy new square with moved piece
				m_board->m_squares[m_selectedSquare->GetID()]->SetOccupiedPiece(m_selectedPiece);

				// Calculate if move has caused check on opponent, then change turns
				if (m_whiteMove)
				{
					if (CalculateAttackingMoves(true))
					{
						m_blackCheck = true;
						UE_LOG(LogTemp, Warning, TEXT("Black in check."));
					}
					m_whiteMove = false;
				}
				else
				{
					if (CalculateAttackingMoves(false))
					{
						m_whiteCheck = true;
						UE_LOG(LogTemp, Warning, TEXT("White in check."));
					}
					m_whiteMove = true;
				}
				break;
			}
		}
	}
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

bool AGame_Controller::CalculateAttackingMoves(bool _isWhite)
{
	// Clear previously attacked squares
	m_whiteAttacking.clear();
	m_blackAttacking.clear();

	std::vector<APiece*> attackingPieces;
	std::vector<int> attackedSquares;

	if (_isWhite)
	{
		attackingPieces = m_whitePieces;
		attackedSquares = m_whiteAttacking;
	}
	else
	{
		attackingPieces = m_blackPieces;
		attackedSquares = m_blackAttacking;
	}

	// Calculate moves for each active black piece
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
	// Erase overlaps (two pieces attacking the same square)
	sort(attackedSquares.begin(), attackedSquares.end());
	attackedSquares.erase(std::unique(attackedSquares.begin(), attackedSquares.end()), attackedSquares.end());

	// If any black piece is attacking the white king
	for (int k = 0; k < attackedSquares.size(); ++k)
	{
		if (m_board->m_squares[attackedSquares[k]]->GetOccupied())
		{
			if (m_board->m_squares[attackedSquares[k]]->GetOccupiedPiece()->IsA(APiece_King::StaticClass()))
			{
				if (!_isWhite)
				{
					if (m_board->m_squares[attackedSquares[k]]->GetOccupiedPiece()->GetIsWhite())
					{
						return true;
					}
				}
				else
				{
					if (!m_board->m_squares[attackedSquares[k]]->GetOccupiedPiece()->GetIsWhite())
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

void AGame_Controller::SimulateMove(APiece* _piece, int _move)
{
	// SIMULATE MOVE:
				//	-	Validate which moves are legal (aren't going to cause check on self)

	// Store temp data
	int currentSquare = _piece->GetSquare();
	int newSquare = m_filteredMoves[_move];
	APiece* newSquarePiece = nullptr;
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
	_piece->SetSquare(m_filteredMoves[_move]);
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
	_piece->SetSquare(currentSquare);
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

std::vector<int> AGame_Controller::FilterRealMoves(APiece* _piece, std::vector<std::vector<int>> _movesToFilter)
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
		return CalculateAttackingMoves(false);
	}
	// Simulate blacks move
	else
	{
		return CalculateAttackingMoves(true);
	}
	// Valid move (won't cause check on self)
	return false;
}

void AGame_Controller::MoveOutOfCheck(std::vector<APiece*> _pieces)
{
	for (int i = 0; i < _pieces.size(); ++i)
	{
		if (_pieces[i] != nullptr)
		{
			APiece* piece = _pieces[i];
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
			UE_LOG(LogTemp, Warning, TEXT("WHITE IN CHECKMATE"));
		}
		else
		{
			m_whiteCheck = false;
			UE_LOG(LogTemp, Warning, TEXT("WHITE NO CHECK"));
		}
	}
	// Black move and black in check
	else if (!m_whiteMove && m_blackCheck)
	{
		MoveOutOfCheck(m_blackPieces);
		if (m_validMoves.size() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("BLACK IN CHECKMATE"));
		}
		else
		{
			m_blackCheck = false;
			UE_LOG(LogTemp, Warning, TEXT("BLACK NO CHECK"));
		}
	}
}