// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Piece_King.generated.h"

/**
 * 
 */
UCLASS()
class VFX_CHESS_API APiece_King : public APiece
{
	GENERATED_BODY()
	
public:
	APiece_King();

	std::vector<std::vector<int>> CalculateMoves();
	void MovePiece(int _id, FVector _dimensions);
	bool GetFirstMove() { return m_firstMove; }

private:
	bool m_firstMove = true;

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
