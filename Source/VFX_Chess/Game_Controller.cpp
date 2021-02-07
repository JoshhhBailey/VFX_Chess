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

	// Mouse cursor
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
	// Clear previous moves
	UnhighlightMoves();
	m_availableMovesCopy.clear();
	SelectPieceOrSquare();
}

void AGame_Controller::SelectPieceOrSquare()
{
	// Detect and store hit object
	FHitResult target(ForceInit);
	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, target);

	if (target.GetActor() != nullptr)
	{
		if (target.GetActor()->IsA(APiece::StaticClass()))
		{
			m_selectedPiece = Cast<APiece>(target.GetActor());	// Cast target actor to APiece to access functions
			if (m_selectedPiece != nullptr)
			{
				m_selectedPiece->SelectPiece();
				m_availableMovesCopy = m_selectedPiece->CalculateMoves();
				HighlightMoves();
			}
		}
	}
}

void AGame_Controller::HighlightMoves()
{
	if (m_availableMovesCopy.size() > 1)
	{
		m_movesHighlighted = true;
		for (int i = 0; i < m_availableMovesCopy.size(); ++i)
		{
			m_board->SetSelectedMaterial(m_availableMovesCopy[i]);
		}
	}
}

void AGame_Controller::UnhighlightMoves()
{
	for (int i = 0; i < m_availableMovesCopy.size(); ++i)
	{
		m_board->ResetMaterial(m_availableMovesCopy[i]);
	}
	m_movesHighlighted = false;
}

void AGame_Controller::MakeMove()
{
	if (m_movesHighlighted)
	{

	}
}