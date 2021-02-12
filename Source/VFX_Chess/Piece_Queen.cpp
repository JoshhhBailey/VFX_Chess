// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece_Queen.h"

APiece_Queen::APiece_Queen()
{
	// Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> queenMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (queenMesh.Succeeded())
	{
		m_mesh->SetStaticMesh(queenMesh.Object);

		// Get mesh dimensions
		SetDimensions(queenMesh.Object->GetBounds().GetBox().GetSize());
	}
}

std::vector<std::vector<int>> APiece_Queen::CalculateMoves()
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

	int currentSquare = GetSquare();
	// Straights
	while (currentSquare < 56)	// Piece not on top edge
	{
		m_U.push_back(currentSquare + 8);
		currentSquare += 8;
	}

	currentSquare = GetSquare();
	while (currentSquare % 8 != 0)	// Piece not at right edge
	{
		m_R.push_back(currentSquare - 1);
		currentSquare -= 1;
	}

	currentSquare = GetSquare();
	while (currentSquare > 7)		// Piece not on bottom edge
	{
		m_D.push_back(currentSquare - 8);
		currentSquare -= 8;
	}

	currentSquare = GetSquare();
	while (currentSquare % 8 != 7)	// Piece not on left edge
	{
		m_L.push_back(currentSquare + 1);
		currentSquare += 1;
	}

	// Diagonals
	currentSquare = GetSquare();
	while (currentSquare % 8 != 7 && currentSquare < 56)	// Piece not on left or top edge
	{
		m_UL.push_back(currentSquare + 9);
		currentSquare += 9;
	}

	currentSquare = GetSquare();
	while (currentSquare < 56 && currentSquare % 8 != 0)	// Piece not on top or right edge
	{
		m_UR.push_back(currentSquare + 7);
		currentSquare += 7;
	}

	currentSquare = GetSquare();
	while (currentSquare % 8 != 0 && currentSquare > 7)	// Piece not on right or bottom edge
	{
		m_DR.push_back(currentSquare - 9);
		currentSquare -= 9;
	}

	currentSquare = GetSquare();
	while (currentSquare > 7 && currentSquare % 8 != 7)	// Piece not on bottom or left edge
	{
		m_DL.push_back(currentSquare - 7);
		currentSquare -= 7;
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

void APiece_Queen::MovePiece(int _id, FVector _dimensions)
{
	float xPos = (_id % 8) * _dimensions.X;
	float yPos = (_id / 8) * _dimensions.Y;

	// Update location
	SetActorLocation({ xPos, yPos, 100 });
	SetSquare(_id);
}