// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece_Pawn.h"

APiece_Pawn::APiece_Pawn()
{
	// ! Change to pawn when available
	// Set blueprint
	static ConstructorHelpers::FObjectFinder<UClass> pawnblueprint(TEXT("Class'/Game/VFX_Chess/Assets/Characters/Rook/Rook_BP.Rook_BP_C'"));
	if (pawnblueprint.Succeeded())
	{
		m_pieceBlueprint = pawnblueprint.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Knight BP does not exist!"));
	}
}

std::vector<std::vector<int>> APiece_Pawn::CalculateMoves()
{
	// Clear previous moves
	m_UL.clear();
	m_U.clear();
	m_UR.clear();
	m_availableMoves.clear();

	// White Pawn
	if (GetIsWhite())
	{
		if (GetSquareID() < 56)	// Not at end of board
		{
			m_U.push_back(GetSquareID() + 8);	// Forward
			if (m_firstMove)
			{
				m_U.push_back(GetSquareID() + 16);	// Double forward
			}
			if (GetSquareID() % 8 != 0)	// Piece not on right edge
			{
				m_UR.push_back(GetSquareID() + 7);	// Diagonal right
			}
			if (GetSquareID() % 8 != 7)	// Piece not on left edge
			{
				m_UL.push_back(GetSquareID() + 9);	// Diagonal left
			}
		}
	}
	// Black Pawn
	else
	{
		if (GetSquareID() > 7)	// Not at end of board
		{
			m_U.push_back(GetSquareID() - 8);
			if (m_firstMove)
			{
				m_U.push_back(GetSquareID() - 16);
			}
			if (GetSquareID() % 8 != 7)	// Piece not on right edge
			{
				m_UR.push_back(GetSquareID() - 7);	// Diagonal right
			}
			if (GetSquareID() % 8 != 0)	// Piece not on left edge
			{
				m_UL.push_back(GetSquareID() - 9);	// Diagonal left
			}
		}
	}

	// Return new available moves
	m_availableMoves.push_back(m_UL);
	m_availableMoves.push_back(m_U);
	m_availableMoves.push_back(m_UR);
	return m_availableMoves;
}

void APiece_Pawn::MovePiece(int _id, FVector _dimensions)
{
	if (m_firstMove)
	{
		m_firstMove = false;
	}
	// Convert id into xy coordinates
	float xPos = (_id % 8) * _dimensions.X;
	float yPos = (_id / 8) * _dimensions.Y;
	
	// Update location
	SetActorLocation({ xPos, yPos, 50.0f });
	SetSquareID(_id);
	m_spawnedBlueprint->SetActorLocation({ xPos, yPos, 50.0f });
}