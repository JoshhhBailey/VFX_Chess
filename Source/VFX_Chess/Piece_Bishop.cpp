///
///  @file Piece_Bishop.cpp
///  @brief Bishop movement logic

#include "Piece_Bishop.h"

APiece_Bishop::APiece_Bishop()
{
	// Set blueprint
	static ConstructorHelpers::FObjectFinder<UClass> bishopBlueprint(TEXT("Class'/Game/VFX_Chess/Assets/Characters/Bishop/Bishop_BP.Bishop_BP_C'"));
	if (bishopBlueprint.Succeeded())
	{
		m_pieceBlueprint = bishopBlueprint.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Bishop BP does not exist!"));
	}
}

std::vector<std::vector<int>> APiece_Bishop::CalculateMoves()
{
	// Clear previous moves
	m_UL.clear();
	m_UR.clear();
	m_DL.clear();
	m_DR.clear();
	m_availableMoves.clear();

	int currentSquare = GetSquareID();

	while (currentSquare % 8 != 7 && currentSquare < 56)	// Piece not on left or top edge
	{
		m_UL.push_back(currentSquare + 9);
		currentSquare += 9;
	}

	currentSquare = GetSquareID();
	while (currentSquare < 56 && currentSquare % 8 != 0)	// Piece not on top or right edge
	{
		m_UR.push_back(currentSquare + 7);
		currentSquare += 7;
	}

	currentSquare = GetSquareID();
	while (currentSquare % 8 != 0 && currentSquare > 7)	// Piece not on right or bottom edge
	{
		m_DR.push_back(currentSquare - 9);
		currentSquare -= 9;
	}

	currentSquare = GetSquareID();
	while (currentSquare > 7 && currentSquare % 8 != 7)	// Piece not on bottom or left edge
	{
		m_DL.push_back(currentSquare - 7);
		currentSquare -= 7;
	}

	// Return new available moves
	m_availableMoves.push_back(m_UL);
	m_availableMoves.push_back(m_UR);
	m_availableMoves.push_back(m_DL);
	m_availableMoves.push_back(m_DR);
	return m_availableMoves;
}

// void APiece_Bishop::MovePiece(int _id, FVector _dimensions)
// {
// 	float xPos = (_id % 8) * _dimensions.X;
// 	float yPos = (_id / 8) * _dimensions.Y;

// 	// Update location
// 	SetActorLocation({ xPos, yPos, 50.0f });
// 	SetSquareID(_id);
// 	m_spawnedBlueprint->SetActorLocation({ xPos, yPos, 50.0f });
// }