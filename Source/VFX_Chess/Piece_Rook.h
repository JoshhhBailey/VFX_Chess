/// \file Piece_Rook.h
/// \brief Rook movement logic
/// \author Josh Bailey
/// \date 09/03/21 Updated to NCCA Coding standard
/// Revision History:
///
/// \todo

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Piece_Rook.generated.h"

/**
 * 
 */
UCLASS()
class VFX_CHESS_API APiece_Rook : public APiece
{
	GENERATED_BODY()

public:
	APiece_Rook();

	std::vector<std::vector<int>> CalculateMoves();
	void MovePiece(int _id, FVector _dimensions);
	bool GetFirstMove() { return m_firstMove; }

private:
	bool m_firstMove = true;
	std::vector<int> m_U;
	std::vector<int> m_R;
	std::vector<int> m_D;
	std::vector<int> m_L;
};
