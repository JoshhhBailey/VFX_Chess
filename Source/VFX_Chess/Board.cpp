// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Piece_Pawn.h"
#include "Piece_Rook.h"
#include "Piece_Bishop.h"
#include "Piece_Knight.h"
#include "Piece_Queen.h"
#include "Piece_King.h"

// Sets default values
ABoard::ABoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();

	SpawnBoard();
	SpawnPieces();
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABoard::SpawnBoard()
{
	// Generate board
	for (int i = 0; i < m_gridWidth * m_gridLength; ++i)
	{
		// Spawn square
		ABoard_Square* square = GetWorld()->SpawnActor<ABoard_Square>(FVector(0, 0, 0), FRotator(0, 0, 0));
		m_board.push_back(square);

		// Set position
		float xPos = (i / m_gridWidth) * m_board[i]->GetDimensions().X;
		float yPos = (i % m_gridLength) * m_board[i]->GetDimensions().Y;
		m_board[i]->SetActorLocation({ xPos, yPos, 0.0f });

		// Set colour
		int materialA = (i / m_gridWidth) % 2;
		int materialB = (i % m_gridLength) % 2;
		bool selectedMaterial = XOR((bool)materialA, (bool)materialB);

		if (selectedMaterial)
		{
			m_board[i]->SetLightMaterial();
		}
		else
		{
			m_board[i]->SetDarkMaterial();
		}
	}
}

void ABoard::SpawnPieces()
{
	// WHITE
	for (int i = 0; i < 8; ++i)
	{
		APiece_Pawn* whitePawn = GetWorld()->SpawnActor<APiece_Pawn>(FVector(0, 0, 0), FRotator(0, 0, 0));
		whitePawn->SetActorLocation({ m_board[i]->GetDimensions().X * i, m_board[i]->GetDimensions().Y, whitePawn->GetDimensions().Z });
		whitePawn->SetLight();
	}

	APiece_Rook* whiteRook_1 = GetWorld()->SpawnActor<APiece_Rook>(FVector(0, 0, 0), FRotator(0, 0, 0));
	whiteRook_1->SetActorLocation({ m_board[0]->GetDimensions().X * 7, 0, whiteRook_1->GetDimensions().Z });
	whiteRook_1->SetLight();

	APiece_Rook* whiteRook_2 = GetWorld()->SpawnActor<APiece_Rook>(FVector(0, 0, 0), FRotator(0, 0, 0));
	whiteRook_2->SetActorLocation({ 0, 0, whiteRook_2->GetDimensions().Z });
	whiteRook_2->SetLight();

	APiece_Knight* whiteKnight_1 = GetWorld()->SpawnActor<APiece_Knight>(FVector(0, 0, 0), FRotator(0, 0, 0));
	whiteKnight_1->SetActorLocation({ m_board[0]->GetDimensions().X * 6, 0, whiteKnight_1->GetDimensions().Z });
	whiteKnight_1->SetLight();

	APiece_Knight* whiteKnight_2 = GetWorld()->SpawnActor<APiece_Knight>(FVector(0, 0, 0), FRotator(0, 0, 0));
	whiteKnight_2->SetActorLocation({ m_board[0]->GetDimensions().X, 0, whiteKnight_2->GetDimensions().Z });
	whiteKnight_2->SetLight();

	APiece_Bishop* whiteBishop_1 = GetWorld()->SpawnActor<APiece_Bishop>(FVector(0, 0, 0), FRotator(0, 0, 0));
	whiteBishop_1->SetActorLocation({ m_board[0]->GetDimensions().X * 5, 0, whiteBishop_1->GetDimensions().Z });
	whiteBishop_1->SetLight();

	APiece_Bishop* whiteBishop_2 = GetWorld()->SpawnActor<APiece_Bishop>(FVector(0, 0, 0), FRotator(0, 0, 0));
	whiteBishop_2->SetActorLocation({ m_board[0]->GetDimensions().X * 2, 0, whiteBishop_2->GetDimensions().Z });
	whiteBishop_2->SetLight();

	APiece_Queen* whiteQueen = GetWorld()->SpawnActor<APiece_Queen>(FVector(0, 0, 0), FRotator(0, 0, 0));
	whiteQueen->SetActorLocation({ m_board[0]->GetDimensions().X * 4, 0, whiteQueen->GetDimensions().Z });
	whiteQueen->SetLight();

	APiece_King* whiteKing = GetWorld()->SpawnActor<APiece_King>(FVector(0, 0, 0), FRotator(0, 0, 0));
	whiteKing->SetActorLocation({ m_board[0]->GetDimensions().X * 3, 0, whiteKing->GetDimensions().Z });
	whiteKing->SetLight();

	// BLACK
	for (int i = 0; i < 8; ++i)
	{
		APiece_Pawn* blackPawn = GetWorld()->SpawnActor<APiece_Pawn>(FVector(0, 0, 0), FRotator(0, 0, 0));
		blackPawn->SetActorLocation({ m_board[i]->GetDimensions().X * i, m_board[i]->GetDimensions().Y * 6, blackPawn->GetDimensions().Z });
		blackPawn->SetDark();
	}

	APiece_Rook* blackRook_1 = GetWorld()->SpawnActor<APiece_Rook>(FVector(0, 0, 0), FRotator(0, 0, 0));
	blackRook_1->SetActorLocation({ m_board[0]->GetDimensions().X * 7, m_board[0]->GetDimensions().Y * 7, blackRook_1->GetDimensions().Z });
	blackRook_1->SetDark();

	APiece_Rook* blackRook_2 = GetWorld()->SpawnActor<APiece_Rook>(FVector(0, 0, 0), FRotator(0, 0, 0));
	blackRook_2->SetActorLocation({ 0, m_board[0]->GetDimensions().Y * 7, blackRook_2->GetDimensions().Z });
	blackRook_2->SetDark();

	APiece_Knight* blackKnight_1 = GetWorld()->SpawnActor<APiece_Knight>(FVector(0, 0, 0), FRotator(0, 0, 0));
	blackKnight_1->SetActorLocation({ m_board[0]->GetDimensions().X * 6, m_board[0]->GetDimensions().Y * 7, blackKnight_1->GetDimensions().Z });
	blackKnight_1->SetDark();

	APiece_Knight* blackKnight_2 = GetWorld()->SpawnActor<APiece_Knight>(FVector(0, 0, 0), FRotator(0, 0, 0));
	blackKnight_2->SetActorLocation({ m_board[0]->GetDimensions().X, m_board[0]->GetDimensions().Y * 7, blackKnight_2->GetDimensions().Z });
	blackKnight_2->SetDark();

	APiece_Bishop* blackBishop_1 = GetWorld()->SpawnActor<APiece_Bishop>(FVector(0, 0, 0), FRotator(0, 0, 0));
	blackBishop_1->SetActorLocation({ m_board[0]->GetDimensions().X * 5, m_board[0]->GetDimensions().Y * 7, blackBishop_1->GetDimensions().Z });
	blackBishop_1->SetDark();

	APiece_Bishop* blackBishop_2 = GetWorld()->SpawnActor<APiece_Bishop>(FVector(0, 0, 0), FRotator(0, 0, 0));
	blackBishop_2->SetActorLocation({ m_board[0]->GetDimensions().X * 2, m_board[0]->GetDimensions().Y * 7, blackBishop_2->GetDimensions().Z });
	blackBishop_2->SetDark();

	APiece_Queen* blackQueen = GetWorld()->SpawnActor<APiece_Queen>(FVector(0, 0, 0), FRotator(0, 0, 0));
	blackQueen->SetActorLocation({ m_board[0]->GetDimensions().X * 3, m_board[0]->GetDimensions().Y * 7, blackQueen->GetDimensions().Z });
	blackQueen->SetDark();

	APiece_King* blackKing = GetWorld()->SpawnActor<APiece_King>(FVector(0, 0, 0), FRotator(0, 0, 0));
	blackKing->SetActorLocation({ m_board[0]->GetDimensions().X * 4, m_board[0]->GetDimensions().Y * 7, blackKing->GetDimensions().Z });
	blackKing->SetDark();
}