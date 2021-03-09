/// \file Piece_Pawn.h
/// \brief Pawn movement logic
/// \author Josh Bailey
/// \date 09/03/21 Updated to NCCA Coding standard
/// Revision History:
///
/// \todo

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Piece_Pawn.generated.h"

/**
 * 
 */
UCLASS()
class VFX_CHESS_API APiece_Pawn : public APiece
{
	GENERATED_BODY()
	
public:
	APiece_Pawn();

	std::vector<std::vector<int>> CalculateMoves();
	void MovePiece(int _id, FVector _dimensions);

private:
	bool m_firstMove = true;
	std::vector<int> m_UL;
	std::vector<int> m_U;
	std::vector<int> m_UR;
};