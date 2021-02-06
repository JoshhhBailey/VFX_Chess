// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Controller.h"

#include "Board.h"
#include "Piece.h"

#include "Piece_Pawn.h"
#include "Piece_Rook.h"
#include "Piece_Bishop.h"
#include "Piece_Knight.h"
#include "Piece_Queen.h"
#include "Piece_King.h"

#include "Game_Player.h"

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

void AGame_Controller::LeftMouseClick()
{
	// Deselect previous piece
	if (this->m_selectedPiece != nullptr)
	{
		this->m_selectedPiece->DeselectPiece();
	}
	SelectPiece();
}

void AGame_Controller::SelectPiece()
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
				m_selectedPiece->CalculateMoves(/* Copy of board */);
			}
		}
	}
}

void AGame_Controller::SpawnPieces()
{
	// WHITE
	for (int i = 0; i < 8; ++i)
	{
		APiece_Pawn* whitePawn = GetWorld()->SpawnActor<APiece_Pawn>(FVector::ZeroVector, FRotator::ZeroRotator);
		whitePawn->SetActorLocation({ m_board->m_squares[i]->GetDimensions().X * i, m_board->m_squares[i]->GetDimensions().Y, whitePawn->GetDimensions().Z });
		whitePawn->SetLight();
		// Give piece an index to the sqaure its currently on
	}

	APiece_Rook* whiteRook_1 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteRook_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 7, 0, whiteRook_1->GetDimensions().Z });
	whiteRook_1->SetLight();

	APiece_Rook* whiteRook_2 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteRook_2->SetActorLocation({ 0, 0, whiteRook_2->GetDimensions().Z });
	whiteRook_2->SetLight();

	APiece_Knight* whiteKnight_1 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteKnight_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 6, 0, whiteKnight_1->GetDimensions().Z });
	whiteKnight_1->SetLight();

	APiece_Knight* whiteKnight_2 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteKnight_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X, 0, whiteKnight_2->GetDimensions().Z });
	whiteKnight_2->SetLight();

	APiece_Bishop* whiteBishop_1 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteBishop_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 5, 0, whiteBishop_1->GetDimensions().Z });
	whiteBishop_1->SetLight();

	APiece_Bishop* whiteBishop_2 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteBishop_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 2, 0, whiteBishop_2->GetDimensions().Z });
	whiteBishop_2->SetLight();

	APiece_Queen* whiteQueen = GetWorld()->SpawnActor<APiece_Queen>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteQueen->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 4, 0, whiteQueen->GetDimensions().Z });
	whiteQueen->SetLight();

	APiece_King* whiteKing = GetWorld()->SpawnActor<APiece_King>(FVector::ZeroVector, FRotator::ZeroRotator);
	whiteKing->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 3, 0, whiteKing->GetDimensions().Z });
	whiteKing->SetLight();

	// BLACK
	for (int i = 0; i < 8; ++i)
	{
		APiece_Pawn* blackPawn = GetWorld()->SpawnActor<APiece_Pawn>(FVector::ZeroVector, FRotator::ZeroRotator);
		blackPawn->SetActorLocation({ m_board->m_squares[i]->GetDimensions().X * i, m_board->m_squares[i]->GetDimensions().Y * 6, blackPawn->GetDimensions().Z });
		blackPawn->SetDark();
	}

	APiece_Rook* blackRook_1 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackRook_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 7, m_board->m_squares[0]->GetDimensions().Y * 7, blackRook_1->GetDimensions().Z });
	blackRook_1->SetDark();

	APiece_Rook* blackRook_2 = GetWorld()->SpawnActor<APiece_Rook>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackRook_2->SetActorLocation({ 0, m_board->m_squares[0]->GetDimensions().Y * 7, blackRook_2->GetDimensions().Z });
	blackRook_2->SetDark();

	APiece_Knight* blackKnight_1 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackKnight_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 6, m_board->m_squares[0]->GetDimensions().Y * 7, blackKnight_1->GetDimensions().Z });
	blackKnight_1->SetDark();

	APiece_Knight* blackKnight_2 = GetWorld()->SpawnActor<APiece_Knight>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackKnight_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X, m_board->m_squares[0]->GetDimensions().Y * 7, blackKnight_2->GetDimensions().Z });
	blackKnight_2->SetDark();

	APiece_Bishop* blackBishop_1 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackBishop_1->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 5, m_board->m_squares[0]->GetDimensions().Y * 7, blackBishop_1->GetDimensions().Z });
	blackBishop_1->SetDark();

	APiece_Bishop* blackBishop_2 = GetWorld()->SpawnActor<APiece_Bishop>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackBishop_2->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 2, m_board->m_squares[0]->GetDimensions().Y * 7, blackBishop_2->GetDimensions().Z });
	blackBishop_2->SetDark();

	APiece_Queen* blackQueen = GetWorld()->SpawnActor<APiece_Queen>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackQueen->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 3, m_board->m_squares[0]->GetDimensions().Y * 7, blackQueen->GetDimensions().Z });
	blackQueen->SetDark();

	APiece_King* blackKing = GetWorld()->SpawnActor<APiece_King>(FVector::ZeroVector, FRotator::ZeroRotator);
	blackKing->SetActorLocation({ m_board->m_squares[0]->GetDimensions().X * 4, m_board->m_squares[0]->GetDimensions().Y * 7, blackKing->GetDimensions().Z });
	blackKing->SetDark();
}