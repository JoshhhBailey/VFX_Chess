/// \file Piece_Queen.h
/// \brief Queen movement logic
/// \author Josh Bailey
/// \date 09/03/21 Updated to NCCA Coding standard
/// Revision History:
///
/// \todo

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Piece_Queen.generated.h"

/**
 * 
 */
UCLASS()
class VFX_CHESS_API APiece_Queen : public APiece
{
	GENERATED_BODY()
	
public:
	APiece_Queen();

	std::vector<std::vector<int>> CalculateMoves();
	void UpdateMaterial();

private:
	// Diagonals
	std::vector<int> m_UL;
	std::vector<int> m_UR;
	std::vector<int> m_DL;
	std::vector<int> m_DR;

	// Straights
	std::vector<int> m_U;
	std::vector<int> m_R;
	std::vector<int> m_D;
	std::vector<int> m_L;
};