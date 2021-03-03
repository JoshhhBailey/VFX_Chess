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

	if (GetWorld()->GetName() == "Main_Level")
	{
		// Spawn board
		m_board = GetWorld()->SpawnActor<ABoard>(FVector::ZeroVector, FRotator::ZeroRotator);
		// Spawn players
		m_playerOne = GetWorld()->SpawnActor<AGame_Player>(FVector(2168.0f, -460.0f, 3560.0f), FRotator(0, 90.0f, 0));
		m_playerTwo = GetWorld()->SpawnActor<AGame_Player>(FVector(2168.0f, 4820.0f, 3560.0f), FRotator(0, -90.0f, 0));
		m_playerTwo->SetIsWhite(false);
		Possess(m_playerOne);

		SpawnPieces();
		UE_LOG(LogTemp, Warning, TEXT("Game has started."));
	}
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
	whiteRook_1->SpawnBlueprint(m_board->m_squares[0]->GetDimensions(), { 0.0f, 90.0f, 0.0f });

	APiece_Rook* whiteRook_2 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteRook_2->SetActorLocation({ 0, 0, whiteRook_2->GetDimensions().Z });
	whiteRook_2->SetSquare(0);
	m_board->m_squares[0]->SetOccupiedPiece(whiteRook_2);
	whiteRook_2->SetID(9);
	m_whitePieces.push_back(whiteRook_2);
	whiteRook_2->SpawnBlueprint(m_board->m_squares[0]->GetDimensions(), { 0.0f, 90.0f, 0.0f });

	APiece_Knight* whiteKnight_1 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteKnight_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 6, 0, whiteKnight_1->GetDimensions().Z });
	whiteKnight_1->SetSquare(6);
	m_board->m_squares[6]->SetOccupiedPiece(whiteKnight_1);
	whiteKnight_1->SetID(10);
	m_whitePieces.push_back(whiteKnight_1);
	whiteKnight_1->SpawnBlueprint(m_board->m_squares[0]->GetDimensions(), { 0.0f, 90.0f, 0.0f });

	APiece_Knight* whiteKnight_2 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteKnight_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X, 0, whiteKnight_2->GetDimensions().Z });
	whiteKnight_2->SetSquare(1);
	m_board->m_squares[1]->SetOccupiedPiece(whiteKnight_2);
	whiteKnight_2->SetID(11);
	m_whitePieces.push_back(whiteKnight_2);
	whiteKnight_2->SpawnBlueprint(m_board->m_squares[0]->GetDimensions(), { 0.0f, 90.0f, 0.0f });

	APiece_Bishop* whiteBishop_1 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteBishop_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 5, 0, whiteBishop_1->GetDimensions().Z });
	whiteBishop_1->SetSquare(5);
	m_board->m_squares[5]->SetOccupiedPiece(whiteBishop_1);
	whiteBishop_1->SetID(12);
	m_whitePieces.push_back(whiteBishop_1);
	whiteBishop_1->SpawnBlueprint(m_board->m_squares[0]->GetDimensions(), { 0.0f, 90.0f, 0.0f });

	APiece_Bishop* whiteBishop_2 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteBishop_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 2, 0, whiteBishop_2->GetDimensions().Z });
	whiteBishop_2->SetSquare(2);
	m_board->m_squares[2]->SetOccupiedPiece(whiteBishop_2);
	whiteBishop_2->SetID(13);
	m_whitePieces.push_back(whiteBishop_2);
	whiteBishop_2->SpawnBlueprint(m_board->m_squares[0]->GetDimensions(), { 0.0f, 90.0f, 0.0f });

	APiece_Queen* whiteQueen = GetWorld()->SpawnActor<APiece_Queen>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteQueen->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 4, 0, whiteQueen->GetDimensions().Z });
	whiteQueen->SetSquare(4);
	m_board->m_squares[4]->SetOccupiedPiece(whiteQueen);
	whiteQueen->SetID(14);
	m_whitePieces.push_back(whiteQueen);
	whiteQueen->SpawnBlueprint(m_board->m_squares[0]->GetDimensions(), { 0.0f, 90.0f, 0.0f });

	APiece_King* whiteKing = GetWorld()->SpawnActor<APiece_King>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteKing->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 3, 0, whiteKing->GetDimensions().Z });
	whiteKing->SetSquare(3);
	m_board->m_squares[3]->SetOccupiedPiece(whiteKing);
	whiteKing->SetID(15);
	m_whitePieces.push_back(whiteKing);
	whiteKing->SpawnBlueprint(m_board->m_squares[0]->GetDimensions(), { 0.0f, 90.0f, 0.0f });

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
	//blackBishop_1->SpawnBlueprint(m_board->m_squares[0]->GetDimensions(), { 0.0f, -90.0f, 0.0f });

	APiece_Bishop* blackBishop_2 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackBishop_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 5, m_board->m_squares[0]->GetDimensions().Y * 7, blackBishop_2->GetDimensions().Z });
	blackBishop_2->SetBlack();
	blackBishop_2->SetSquare(61);
	m_board->m_squares[61]->SetOccupiedPiece(blackBishop_2);
	blackBishop_2->SetID(13);
	m_blackPieces.push_back(blackBishop_2);
	//blackBishop_2->SpawnBlueprint(m_board->m_squares[0]->GetDimensions(), { 0.0f, -90.0f, 0.0f });

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
	if (m_selectedPiece != nullptr)
	{
		m_selectedPiece->DeselectPiece();
	}

	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, m_target);
	UE_LOG(LogTemp, Warning, TEXT("Target: %s"), *FString(m_target.GetActor()->GetName()));

	m_target.GetActor()->GetParentActor();

	// Clicked something
	if (m_target.GetActor() != nullptr)
	{
		bool enemyPieceSelected = false;
		
			// Piece selected
		if (m_target.GetActor()->IsA(APiece::StaticClass()))
		{
			m_targetPiece = Cast<APiece>(m_target.GetActor());

			if (m_selectedPiece != nullptr)
			{
				// Different colour piece
				if (m_selectedPiece->GetIsWhite() != m_targetPiece->GetIsWhite())
				{
					enemyPieceSelected = true;
				}
			}
			
			// Same colour piece
			if (!enemyPieceSelected)
			{
				// Clear data from previously selected piece
				UnhighlightMoves();
				m_validMoves.clear();
				// Highlight piece and calculate moves
				SelectPiece();
			}
		}
		// Square selected
		if (m_target.GetActor()->IsA(ABoard_Square::StaticClass()) || enemyPieceSelected)
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
				if (!promoting)
				{
					m_selectedPiece = nullptr;
				}
			}
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
			int square = m_targetPiece->GetSquare();
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
					if (!m_selectedSquare->GetOccupied() && abs(m_selectedPiece->GetSquare() - m_selectedSquare->GetID() != 8))
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
					if (m_selectedPiece->IsA(APiece_Pawn::StaticClass()) && abs(m_selectedPiece->GetSquare() - m_selectedSquare->GetID()) == 16)
					{
						m_enPassantVictim = m_selectedPiece;
					}
					else
					{
						m_enPassant = false;
						m_enPassantVictim = nullptr;
					}

					// Unoccupy previous square
					m_board->m_squares[m_selectedPiece->GetSquare()]->RemoveOccupiedPiece();

					// Move piece and assign to new square
					m_selectedPiece->MovePiece(m_selectedSquare->GetID(), m_selectedSquare->GetDimensions());

					// Occupy new square with moved piece
					m_board->m_squares[m_selectedSquare->GetID()]->SetOccupiedPiece(m_selectedPiece);
				}

				// PAWN PROMOTION
				if (m_selectedPiece->IsA(APiece_Pawn::StaticClass()))
				{
					// White pawn reached end of board
					if (m_selectedPiece->GetIsWhite() && m_selectedPiece->GetSquare() > 55)
					{
						promoting = true;
						PromotedPieceUI(m_selectedPiece->GetIsWhite());
					}
					// Black pawn reached end of board
					else if (!m_selectedPiece->GetIsWhite() && m_selectedPiece->GetSquare() < 8)
					{
						promoting = true;
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
					//UnPossess();
					//Possess(m_playerTwo);
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
					//UnPossess();
					//Possess(m_playerOne);
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

	std::vector<APiece*> attackingPieces;
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

	APiece* piece;
	std::vector<APiece*> pieces;

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
	Stalemate();
}

int AGame_Controller::PromotePawn(int _pieceID)
{
	int pieceID = m_selectedPiece->GetID();
	int squareID = m_selectedPiece->GetSquare();
	bool isWhite = m_selectedPiece->GetIsWhite();

	m_selectedPiece->Destroy();

	int xPos = squareID % 8;
	int yPos = squareID / 8;

	APiece* promotedPawn = nullptr;
	if (_pieceID == 1)	// Knight
	{
		promotedPawn = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	else if (_pieceID == 2)	// Bishop
	{
		promotedPawn = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	else if (_pieceID == 3)	// Rook
	{
		promotedPawn = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	else if (_pieceID == 4)	// Queen
	{
		promotedPawn = GetWorld()->SpawnActor<APiece_Queen>(FVector::ZeroVector, FRotator::ZeroRotator);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid piece ID for pawn promotion!"));
	}

	promotedPawn->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * xPos, m_board->m_squares[0]->GetDimensions().Y * yPos, promotedPawn->GetDimensions().Z });
	promotedPawn->SetSquare(squareID);
	m_board->m_squares[squareID]->SetOccupiedPiece(promotedPawn);
	promotedPawn->SetID(pieceID);

	// Update active pieces
	if (isWhite)
	{
		m_whitePieces[pieceID] = promotedPawn;
	}
	else
	{
		promotedPawn->SetBlack();
		m_blackPieces[pieceID] = promotedPawn;
	}

	m_selectedPiece = nullptr;
	promoting = false;
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
	m_board->m_squares[m_selectedPiece->GetSquare()]->RemoveOccupiedPiece();
	// Move piece and assign to new square
	m_selectedPiece->MovePiece(m_selectedSquare->GetID(), m_selectedSquare->GetDimensions());
	// Occupy new square with moved piece
	m_board->m_squares[m_selectedSquare->GetID()]->SetOccupiedPiece(m_selectedPiece);

	// ROOK
	APiece* rook = m_board->m_squares[_rookPos]->GetOccupiedPiece();
	// Unoccupy previous square
	m_board->m_squares[_rookPos]->RemoveOccupiedPiece();
	// Move piece and assign to new square
	rook->MovePiece(_rookTarget, m_selectedSquare->GetDimensions());
	// Occupy new square with moved piece
	m_board->m_squares[_rookTarget]->SetOccupiedPiece(rook);
}

void AGame_Controller::EnPassant()
{
	int currentSquare = m_selectedPiece->GetSquare();
	if (m_selectedPiece->GetSquare() % 8 != 7)	// Not left side of board
	{
		if (m_board->m_squares[currentSquare + 1]->GetOccupied())	// Square to left
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
	if (m_selectedPiece->GetSquare() % 8 != 0)	// Not right side of board
	{
		if (m_board->m_squares[currentSquare - 1]->GetOccupied())	// Square to right
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