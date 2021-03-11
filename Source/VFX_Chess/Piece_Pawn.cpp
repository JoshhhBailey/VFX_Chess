///
///  @file Piece_Pawn.cpp
///  @brief Pawn movement logic

#include "Piece_Pawn.h"

APiece_Pawn::APiece_Pawn()
{
	// Set blueprint
	static ConstructorHelpers::FObjectFinder<UClass> pawnblueprint(TEXT("Class'/Game/VFX_Chess/Assets/Characters/Pawn/Pawn_BP.Pawn_BP_C'"));
	if (pawnblueprint.Succeeded())
	{
		m_pieceBlueprint = pawnblueprint.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn BP does not exist!"));
	}

	// Set light material
	static ConstructorHelpers::FObjectFinder<UMaterial> lightMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Pieces/Pawn/pawnWhite_MAT.pawnWhite_MAT'"));
	if (lightMaterial.Object != NULL)
	{
		m_lightMaterial = (UMaterial*)lightMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn light material does not exist!"));
	}

	// Set dark material
	static ConstructorHelpers::FObjectFinder<UMaterial> darkMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Pieces/Pawn/pawnBlack_MAT.pawnBlack_MAT'"));
	if (darkMaterial.Object != NULL)
	{
		m_darkMaterial = (UMaterial*)darkMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pawn dark material does not exist!"));
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
		if (GetSquareID() < 56) // Not at end of board
		{
			m_U.push_back(GetSquareID() + 8); // Forward
			if (m_firstMove)
			{
				m_U.push_back(GetSquareID() + 16); // Double forward
			}
			if (GetSquareID() % 8 != 0) // Piece not on right edge
			{
				m_UR.push_back(GetSquareID() + 7); // Diagonal right
			}
			if (GetSquareID() % 8 != 7) // Piece not on left edge
			{
				m_UL.push_back(GetSquareID() + 9); // Diagonal left
			}
		}
	}
	// Black Pawn
	else
	{
		if (GetSquareID() > 7) // Not at end of board
		{
			m_U.push_back(GetSquareID() - 8);
			if (m_firstMove)
			{
				m_U.push_back(GetSquareID() - 16);
			}
			if (GetSquareID() % 8 != 7) // Piece not on right edge
			{
				m_UR.push_back(GetSquareID() - 7); // Diagonal right
			}
			if (GetSquareID() % 8 != 0) // Piece not on left edge
			{
				m_UL.push_back(GetSquareID() - 9); // Diagonal left
			}
		}
	}

	// Return new available moves
	m_availableMoves.push_back(m_UL);
	m_availableMoves.push_back(m_U);
	m_availableMoves.push_back(m_UR);
	return m_availableMoves;
}

void APiece_Pawn::UpdateMaterial()
{
	// Early return
	if (m_skeletalMesh == nullptr)
	{
		return;
	}

	UMaterial* resultMaterial;
	// Get correct material
	if (GetIsSelected())
	{
		resultMaterial = m_selectedMaterial;
	}
	else if (GetIsWhite())
	{
		resultMaterial = m_lightMaterial;
	}
	else
	{
		resultMaterial = m_darkMaterial;
	}
	// Apply material
	for (int materialSlotIndex = 0; materialSlotIndex < m_skeletalMesh->GetNumMaterials(); materialSlotIndex++)
	{
		m_skeletalMesh->SetMaterial(materialSlotIndex, resultMaterial);
	}
}