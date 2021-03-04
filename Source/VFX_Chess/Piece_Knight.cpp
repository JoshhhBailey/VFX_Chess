// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece_Knight.h"

APiece_Knight::APiece_Knight()
{
	// Set blueprint
	static ConstructorHelpers::FObjectFinder<UClass> knightBlueprint(TEXT("Class'/Game/VFX_Chess/Assets/Characters/Knight/Knight_BP.Knight_BP_C'"));
	if (knightBlueprint.Succeeded())
	{
		m_pieceBlueprint = knightBlueprint.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Knight BP does not exist!"));
	}
}

std::vector<std::vector<int>> APiece_Knight::CalculateMoves()
{
	// Clear previous moves
	m_UL.clear();
	m_UR.clear();
	m_RU.clear();
	m_RD.clear();
	m_DR.clear();
	m_DL.clear();
	m_LD.clear();
	m_LU.clear();
	m_availableMoves.clear();

	if (GetSquareID() < 47 && GetSquareID() % 8 != 7)	// UL
	{
		m_UL.push_back(GetSquareID() + 17);
	}

	if (GetSquareID() < 48 && GetSquareID() % 8 != 0)	// UR
	{
		m_UR.push_back(GetSquareID() + 15);
	}

	if (GetSquareID() < 56 && GetSquareID() % 8 != 0 && GetSquareID() % 8 != 1)	// RU
	{
		m_RU.push_back(GetSquareID() + 6);
	}

	if (GetSquareID() > 7 && GetSquareID() % 8 != 0 && GetSquareID() % 8 != 1) // RD
	{
		m_RD.push_back(GetSquareID() - 10);
	}

	if (GetSquareID() > 15 && GetSquareID() % 8 != 0) // DR
	{
		m_DR.push_back(GetSquareID() - 17);
	}

	if (GetSquareID() > 15 && GetSquareID() % 8 != 7)	// DL
	{
		m_DL.push_back(GetSquareID() - 15);
	}

	if (GetSquareID() > 7 && GetSquareID() % 8 != 7 && GetSquareID() % 8 != 6) // LD
	{
		m_LD.push_back(GetSquareID() - 6);
	}

	if (GetSquareID() < 56 && GetSquareID() % 8 != 7 && GetSquareID() % 8 != 6) // LU
	{
		m_LU.push_back(GetSquareID() + 10);
	}

	// Return new available moves
	m_availableMoves.push_back(m_UL);
	m_availableMoves.push_back(m_UR);
	m_availableMoves.push_back(m_RU);
	m_availableMoves.push_back(m_RD);
	m_availableMoves.push_back(m_DR);
	m_availableMoves.push_back(m_DL);
	m_availableMoves.push_back(m_LD);
	m_availableMoves.push_back(m_LU);
	return m_availableMoves;
}

void APiece_Knight::MovePiece(int _id, FVector _dimensions)
{
	float xPos = (_id % 8) * _dimensions.X;
	float yPos = (_id / 8) * _dimensions.Y;

	// Update location
	SetActorLocation({ xPos, yPos, 50.0f });
	SetSquareID(_id);
	m_spawnedBlueprint->SetActorLocation({ xPos, yPos, 50.0f });
}