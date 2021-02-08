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

void APiece_Pawn::MovePiece(int _id, FVector _dimensions)
{
	UE_LOG(LogTemp, Warning, TEXT("before. %d"), this->GetSquare());
	if (GetFirstMove())
	{
		SetFirstMove(false);
	}
	// Convert id into xy coordinate
	float xPos = (_id % 8) * _dimensions.X;
	float yPos = (_id / 8) * _dimensions.Y;
	
	// Update location
	this->SetActorLocation({ xPos, yPos, 100 });
	this->SetSquare(_id);
	UE_LOG(LogTemp, Warning, TEXT("after. %d"), this->GetSquare());
	UE_LOG(LogTemp, Warning, TEXT("Location moved."));
}