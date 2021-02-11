// Fill out your copyright notice in the Description page of Project Settings.

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
	std::vector<int> m_UL;
	std::vector<int> m_U;
	std::vector<int> m_UR;

	void MovePiece(int _id, FVector _dimensions);
	bool GetFirstMove() { return m_firstMove; }
	void SetFirstMove(bool _bool) { m_firstMove = _bool; }

private:
	bool m_firstMove = true;
};
