// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece_Pawn.h"

APiece_Pawn::APiece_Pawn()
{
	// Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> pawnMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	if (pawnMesh.Succeeded())
	{
		m_mesh->SetStaticMesh(pawnMesh.Object);
		m_mesh->SetRelativeScale3D({0.5f, 0.5f, 0.5f});

		// Get mesh dimensions
		SetDimensions(pawnMesh.Object->GetBounds().GetBox().GetSize());
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
		m_U.push_back(GetSquare() + 8);	// Forward
		if (GetFirstMove())
		{
			m_U.push_back(GetSquare() + 16);	// Double forward
		}
		if (GetSquare() % 8 != 0)	// Piece not on right edge
		{
			m_UR.push_back(GetSquare() + 7);	// Diagonal right
		}
		if (GetSquare() % 8 != 7)	// Piece not on left edge
		{
			m_UL.push_back(GetSquare() + 9);	// Diagonal left
		}
	}
	// Black Pawn
	else
	{
		m_U.push_back(GetSquare() - 8);
		if (GetFirstMove())
		{
			m_U.push_back(GetSquare() - 16);
		}
		if (GetSquare() % 8 != 7)	// Piece not on right edge
		{
			m_UR.push_back(GetSquare() - 7);	// Diagonal right
		}
		if (GetSquare() % 8 != 0)	// Piece not on left edge
		{
			m_UL.push_back(GetSquare() - 9);	// Diagonal left
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
	UE_LOG(LogTemp, Warning, TEXT("before. %d"), this->GetSquare());
	if (GetFirstMove())
	{
		SetFirstMove(false);
	}
	// Convert id into xy coordinates
	float xPos = (_id % 8) * _dimensions.X;
	float yPos = (_id / 8) * _dimensions.Y;
	
	// Update location
	this->SetActorLocation({ xPos, yPos, 100 });
	this->SetSquare(_id);
	UE_LOG(LogTemp, Warning, TEXT("after. %d"), this->GetSquare());
	UE_LOG(LogTemp, Warning, TEXT("Location moved."));
}