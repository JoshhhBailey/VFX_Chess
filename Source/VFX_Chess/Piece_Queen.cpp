///
///  @file Piece_Queen.cpp
///  @brief Queen movement logic

#include "Piece_Queen.h"

APiece_Queen::APiece_Queen()
{
	// Set blueprint
	static ConstructorHelpers::FObjectFinder<UClass> queenBlueprint(TEXT("Class'/Game/VFX_Chess/Assets/Characters/Queen/Queen_BP.Queen_BP_C'"));
	if (queenBlueprint.Succeeded())
	{
		m_pieceBlueprint = queenBlueprint.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Queen BP does not exist!"));
	}

	// Set light material
	static ConstructorHelpers::FObjectFinder<UMaterial> lightMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Pieces/Queen/queenWhite_MAT.queenWhite_MAT'"));
	if (lightMaterial.Object != NULL)
	{
		m_lightMaterial = (UMaterial*)lightMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Queen light material does not exist!"));
	}

	// Set dark material
	static ConstructorHelpers::FObjectFinder<UMaterial> darkMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Pieces/Queen/queenBlack_MAT.queenBlack_MAT'"));
	if (darkMaterial.Object != NULL)
	{
		m_darkMaterial = (UMaterial*)darkMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Queen dark material does not exist!"));
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

	int currentSquare = GetSquareID();
	// Straights
	while (currentSquare < 56)	// Piece not on top edge
	{
		m_U.push_back(currentSquare + 8);
		currentSquare += 8;
	}

	currentSquare = GetSquareID();
	while (currentSquare % 8 != 0)	// Piece not at right edge
	{
		m_R.push_back(currentSquare - 1);
		currentSquare -= 1;
	}

	currentSquare = GetSquareID();
	while (currentSquare > 7)		// Piece not on bottom edge
	{
		m_D.push_back(currentSquare - 8);
		currentSquare -= 8;
	}

	currentSquare = GetSquareID();
	while (currentSquare % 8 != 7)	// Piece not on left edge
	{
		m_L.push_back(currentSquare + 1);
		currentSquare += 1;
	}

	// Diagonals
	currentSquare = GetSquareID();
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
