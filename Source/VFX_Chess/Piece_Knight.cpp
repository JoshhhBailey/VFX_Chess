///
///  @file Piece_Knight.cpp
///  @brief Knight movement logic

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

	// Set light material
	static ConstructorHelpers::FObjectFinder<UMaterial> lightMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Pieces/Knight/knightWhite_MAT.knightWhite_MAT'"));
	if (lightMaterial.Object != NULL)
	{
		m_lightMaterial = (UMaterial*)lightMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Knight light material does not exist!"));
	}

	// Set dark material
	static ConstructorHelpers::FObjectFinder<UMaterial> darkMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Pieces/Knight/knightBlack_MAT.knightBlack_MAT'"));
	if (darkMaterial.Object != NULL)
	{
		m_darkMaterial = (UMaterial*)darkMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Knight dark material does not exist!"));
	}

	// Set prop light material
	static ConstructorHelpers::FObjectFinder<UMaterial> propLightMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Pieces/Knight/Sword/swordWhite_MAT.swordWhite_MAT'"));
	if (propLightMaterial.Object != NULL)
	{
		m_propLightMaterial = (UMaterial*)propLightMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Knight light prop material does not exist!"));
	}

	// Set prop dark material
	static ConstructorHelpers::FObjectFinder<UMaterial> propDarkMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Pieces/Knight/Sword/swordBlack_MAT.swordBlack_MAT'"));
	if (propDarkMaterial.Object != NULL)
	{
		m_propDarkMaterial = (UMaterial*)propDarkMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Knight dark prop material does not exist!"));
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