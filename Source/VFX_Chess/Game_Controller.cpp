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
	// WHITE
	for (int i = 0; i < 8; ++i)
	{
		APiece_Pawn* whitePawn = GetWorld()->SpawnActor<APiece_Pawn>(FVector::ZeroVector, FRotator::ZeroRotator);
		whitePawn->SetActorLocation({ m_board->m_squares[i]->GetDimensions().X * i, m_board->m_squares[i]->GetDimensions().Y, whitePawn->GetDimensions().Z });
		whitePawn->SetSquare(i + 8);
		m_board->m_squares[i + 8]->SetOccupied(true);
		m_board->m_squares[i + 8]->SetOccupiedPiece(whitePawn);
	}

	APiece_Rook* whiteRook_1 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteRook_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 7, 0, whiteRook_1->GetDimensions().Z });

	APiece_Rook* whiteRook_2 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteRook_2->SetActorLocation({ 0, 0, whiteRook_2->GetDimensions().Z });

	APiece_Knight* whiteKnight_1 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteKnight_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 6, 0, whiteKnight_1->GetDimensions().Z });

	APiece_Knight* whiteKnight_2 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteKnight_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X, 0, whiteKnight_2->GetDimensions().Z });

	APiece_Bishop* whiteBishop_1 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteBishop_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 5, 0, whiteBishop_1->GetDimensions().Z });

	APiece_Bishop* whiteBishop_2 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteBishop_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 2, 0, whiteBishop_2->GetDimensions().Z });

	APiece_Queen* whiteQueen = GetWorld()->SpawnActor<APiece_Queen>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteQueen->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 4, 0, whiteQueen->GetDimensions().Z });

	APiece_King* whiteKing = GetWorld()->SpawnActor<APiece_King>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteKing->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 3, 0, whiteKing->GetDimensions().Z });

	// BLACK
	for (int i = 0; i < 8; ++i)
	{
		APiece_Pawn* blackPawn = GetWorld()->SpawnActor<APiece_Pawn>(FVector::ZeroVector, FRotator::ZeroRotator);
		blackPawn->SetActorLocation({ m_board->m_squares[i]->GetDimensions().X * i, m_board->m_squares[i]->GetDimensions().Y * 6, blackPawn->GetDimensions().Z });
		blackPawn->SetBlack();
		blackPawn->SetSquare(i + 48);
		m_board->m_squares[i + 48]->SetOccupied(true);
		m_board->m_squares[i + 48]->SetOccupiedPiece(blackPawn);
	}

	APiece_Rook* blackRook_1 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackRook_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 7, m_board->m_squares[0]->GetDimensions().Y * 7, blackRook_1->GetDimensions().Z });
	blackRook_1->SetBlack();

	APiece_Rook* blackRook_2 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackRook_2->SetActorLocation({ 0, m_board->m_squares[0]->GetDimensions().Y * 7, blackRook_2->GetDimensions().Z });
	blackRook_2->SetBlack();

	APiece_Knight* blackKnight_1 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackKnight_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 6, m_board->m_squares[0]->GetDimensions().Y * 7, blackKnight_1->GetDimensions().Z });
	blackKnight_1->SetBlack();

	APiece_Knight* blackKnight_2 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackKnight_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X, m_board->m_squares[0]->GetDimensions().Y * 7, blackKnight_2->GetDimensions().Z });
	blackKnight_2->SetBlack();

	APiece_Bishop* blackBishop_1 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackBishop_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 5, m_board->m_squares[0]->GetDimensions().Y * 7, blackBishop_1->GetDimensions().Z });
	blackBishop_1->SetBlack();

	APiece_Bishop* blackBishop_2 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackBishop_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 2, m_board->m_squares[0]->GetDimensions().Y * 7, blackBishop_2->GetDimensions().Z });
	blackBishop_2->SetBlack();

	APiece_Queen* blackQueen = GetWorld()->SpawnActor<APiece_Queen>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackQueen->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 3, m_board->m_squares[0]->GetDimensions().Y * 7, blackQueen->GetDimensions().Z });
	blackQueen->SetBlack();

	APiece_King* blackKing = GetWorld()->SpawnActor<APiece_King>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackKing->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 4, m_board->m_squares[0]->GetDimensions().Y * 7, blackKing->GetDimensions().Z });
	blackKing->SetBlack();
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
			UnhighlightMoves();
			m_filteredMoves.clear();	// ?
			SelectPiece();
		}
		// Square selected
		else if (m_target.GetActor()->IsA(ABoard_Square::StaticClass()))
		{
			SelectSquare();
			UnhighlightMoves();
			m_filteredMoves.clear();	// ?
		}
	}
	else
	{
		UnhighlightMoves();
		m_filteredMoves.clear();
	}
}

void AGame_Controller::SelectPiece()
{
	UE_LOG(LogTemp, Warning, TEXT("Piece selected."));
	m_selectedPiece = Cast<APiece>(m_target.GetActor());
	m_selectedPiece->SelectPiece();
	m_availableMovesCopy = m_selectedPiece->CalculateMoves();
	FilterMoves();		// Remove moves blocked by same colour pieces
	HighlightMoves();
}

void AGame_Controller::SelectSquare()
{
	UE_LOG(LogTemp, Warning, TEXT("Square selected."));
	if (m_movesHighlighted)
	{
		m_selectedSquare = Cast<ABoard_Square>(m_target.GetActor());
		for (int i = 0; i < m_filteredMoves.size(); ++i)
		{
			// Check if selected square is a highlighted available move
			if (m_filteredMoves[i] == m_selectedSquare->GetID())
			{
				if (m_selectedSquare->GetOccupied())
				{
					// Kill piece
					m_selectedSquare->GetOccupiedPiece()->Destroy();
				}
				// Unoccupy previous square
				m_board->m_squares[m_selectedPiece->GetSquare()]->RemoveOccupiedPiece();

				// Move piece and assign to new square
				m_selectedPiece->MovePiece(m_selectedSquare->GetID(), m_selectedSquare->GetDimensions());

				// Occupy new square
				m_board->m_squares[m_selectedSquare->GetID()]->SetOccupied(true);
				m_board->m_squares[m_selectedSquare->GetID()]->SetOccupiedPiece(m_selectedPiece);
			}
		}
	}
}

void AGame_Controller::HighlightMoves()
{
	if (m_filteredMoves.size() > 0)
	{
		m_movesHighlighted = true;
		for (int i = 0; i < m_filteredMoves.size(); ++i)
		{
			// Occupied
			if (m_board->m_squares[m_filteredMoves[i]]->GetOccupied())
			{
				m_board->SetEnemyMaterial(m_filteredMoves[i]);
			}
			else
			{
				m_board->SetSelectedMaterial(m_filteredMoves[i]);
			}
		}
	}
}

void AGame_Controller::UnhighlightMoves()
{
	for (int i = 0; i < m_filteredMoves.size(); ++i)
	{
		m_board->ResetMaterial(m_filteredMoves[i]);
	}
	m_movesHighlighted = false;
}


void AGame_Controller::FilterMoves()
{
	// Loop all available moves
	for (int i = 0; i < m_availableMovesCopy.size(); ++i)
	{
		for (int j = 0; j < m_availableMovesCopy[i].size(); ++j)
		{
			// PAWN UNIQUE CASE
			if (m_selectedPiece->IsA(APiece_Pawn::StaticClass()))
			{
				// UL or UR moves
				if (i == 0 || i == 2)
				{
					// Occupied ...
					if (m_board->m_squares[m_availableMovesCopy[i][j]]->GetOccupied())
					{
						// (and I am white)
						if (m_selectedPiece->GetIsWhite())
						{
							// ... by a black piece
							if (!m_board->m_squares[m_availableMovesCopy[i][j]]->GetOccupiedPiece()->GetIsWhite())
							{
								m_filteredMoves.push_back(m_availableMovesCopy[i][j]);
							}
						}
						// (and I am black)
						else
						{
							// ... by a white piece
							if (m_board->m_squares[m_availableMovesCopy[i][j]]->GetOccupiedPiece()->GetIsWhite())
							{
								m_filteredMoves.push_back(m_availableMovesCopy[i][j]);
							}
						}
					}
				}
				else
				{
					// Occupied
					if (m_board->m_squares[m_availableMovesCopy[i][j]]->GetOccupied())
					{
						break;
					}
					// Not occupied
					else
					{
						m_filteredMoves.push_back(m_availableMovesCopy[i][j]);
					}
				}
			}
			// ALL OTHER PIECES
			else
			{
				// Occupied
				if (m_board->m_squares[m_availableMovesCopy[i][j]]->GetOccupied())
				{
					// White piece
					if (m_board->m_squares[m_availableMovesCopy[i][j]]->GetOccupiedPiece()->GetIsWhite())
					{
						break;
					}
					// Black piece
					else
					{
						m_filteredMoves.push_back(m_availableMovesCopy[i][j]);
						break;
					}
				}
				// Not occupied
				else
				{
					m_filteredMoves.push_back(m_availableMovesCopy[i][j]);
				}
			}
		}
	}
}