/// \file Piece_Knight.h
/// \brief Knight movement logic
/// \author Josh Bailey
/// \date 09/03/21 Updated to NCCA Coding standard
/// Revision History:
///
/// \todo

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Piece_Knight.generated.h"

/**
 * 
 */
UCLASS()
class VFX_CHESS_API APiece_Knight : public APiece
{
	GENERATED_BODY()
	
public:
	APiece_Knight();

	std::vector<std::vector<int>> CalculateMoves();
	void UpdateMaterial();

private:
	std::vector<int> m_UL;
	std::vector<int> m_UR;
	std::vector<int> m_RU;
	std::vector<int> m_RD;
	std::vector<int> m_DR;
	std::vector<int> m_DL;
	std::vector<int> m_LD;
	std::vector<int> m_LU;
};
