// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece_King.h"

APiece_King::APiece_King()
{
	// Set blueprint
	static ConstructorHelpers::FObjectFinder<UClass> kingBlueprint(TEXT("Class'/Game/VFX_Chess/Assets/Characters/King/King_BP.King_BP_C'"));
	if (kingBlueprint.Succeeded())
	{
		m_pieceBlueprint = kingBlueprint.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("King BP does not exist!"));
	}
}

std::vector<std::vector<int>> APiece_King::CalculateMoves()
{
	// Clear previous moves
	m_U.clear();
	m_R.clear();
	m_D.clear();
	m_L.clear();
	m_UL.clear();
	m_UR.clear();
	m_DL.clear();
	m_DR.clear();
	m_availableMoves.clear();

	if (GetSquare() < 56)	// Piece not on top edge
	{
		m_U.push_back(GetSquare() + 8);
	}

	if (GetSquare() % 8 != 0)	// Piece not at right edge
	{
		m_R.push_back(GetSquare() - 1);
	}

	if (GetSquare() > 7)		// Piece not on bottom edge
	{
		m_D.push_back(GetSquare() - 8);
	}

	if (GetSquare() % 8 != 7)	// Piece not on left edge
	{
		m_L.push_back(GetSquare() + 1);
	}

	// Diagonals
	if (GetSquare() % 8 != 7 && GetSquare() < 56)	// Piece not on left or top edge
	{
		m_UL.push_back(GetSquare() + 9);
	}

	if (GetSquare() < 56 && GetSquare() % 8 != 0)	// Piece not on top or right edge
	{
		m_UR.push_back(GetSquare() + 7);
	}

	if (GetSquare() % 8 != 0 && GetSquare() > 7)	// Piece not on right or bottom edge
	{
		m_DR.push_back(GetSquare() - 9);
	}

	if (GetSquare() > 7 && GetSquare() % 8 != 7)	// Piece not on bottom or left edge
	{
		m_DL.push_back(GetSquare() - 7);
	}

	// Return new available moves
	m_availableMoves.push_back(m_U);
	m_availableMoves.push_back(m_R);
	m_availableMoves.push_back(m_D);
	m_availableMoves.push_back(m_L);
	m_availableMoves.push_back(m_UL);
	m_availableMoves.push_back(m_UR);
	m_availableMoves.push_back(m_DL);
	m_availableMoves.push_back(m_DR);
	return m_availableMoves;
}

void APiece_King::MovePiece(int _id, FVector _dimensions)
{
	if (m_firstMove)
	{
		m_firstMove = false;
	}

	float xPos = (_id % 8) * _dimensions.X;
	float yPos = (_id / 8) * _dimensions.Y;

	// Update location
	SetActorLocation({ xPos, yPos, 100 });
	SetSquare(_id);
	m_spawnedBlueprint->SetActorLocation({ xPos, yPos, 100.0f });
}