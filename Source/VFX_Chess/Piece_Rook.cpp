///
///  @file Piece_Rook.cpp
///  @brief Rook movement logic

#include "Piece_Rook.h"

APiece_Rook::APiece_Rook()
{
	// Set blueprint
	static ConstructorHelpers::FObjectFinder<UClass> rookBlueprint(TEXT("Class'/Game/VFX_Chess/Assets/Characters/Rook/Rook_BP.Rook_BP_C'"));
	if (rookBlueprint.Succeeded())
	{
		m_pieceBlueprint = rookBlueprint.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Rook BP does not exist!"));
	}

	// Set light material
	static ConstructorHelpers::FObjectFinder<UMaterial> lightMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Pieces/Rook/rookWhite_MAT.rookWhite_MAT'"));
	if (lightMaterial.Object != NULL)
	{
		m_lightMaterial = (UMaterial*)lightMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Rook light material does not exist!"));
	}

	// Set dark material
	static ConstructorHelpers::FObjectFinder<UMaterial> darkMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Pieces/Rook/rookBlack_MAT.rookBlack_MAT'"));
	if (darkMaterial.Object != NULL)
	{
		m_darkMaterial = (UMaterial*)darkMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Rook dark material does not exist!"));
	}
}

std::vector<std::vector<int>> APiece_Rook::CalculateMoves()
{
	// Clear previous moves
	m_U.clear();
	m_R.clear();
	m_D.clear();
	m_L.clear();
	m_availableMoves.clear();

	int currentSquare = GetSquareID();

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

	// Return new available moves
	m_availableMoves.push_back(m_U);
	m_availableMoves.push_back(m_R);
	m_availableMoves.push_back(m_D);
	m_availableMoves.push_back(m_L);
	return m_availableMoves;
}