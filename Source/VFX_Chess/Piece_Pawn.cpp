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

std::vector<int> APiece_Pawn::CalculateMoves()
{
	// Clear previous moves
	m_availableMoves.clear();
	if (GetIsWhite())
	{
		m_availableMoves.push_back(GetSquare() + 8);
		if (GetFirstMove())
		{
			m_availableMoves.push_back(GetSquare() + 16);
		}
	}
	else
	{
		m_availableMoves.push_back(GetSquare() - 8);
		if (GetFirstMove())
		{
			m_availableMoves.push_back(GetSquare() - 16);
		}
	}
	return m_availableMoves;
}