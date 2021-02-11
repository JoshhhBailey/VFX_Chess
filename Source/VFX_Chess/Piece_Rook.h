// Fill out your copyright notice in the Description page of Project Settings.

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

private:
	std::vector<int> m_U;
	std::vector<int> m_R;
	std::vector<int> m_D;
	std::vector<int> m_L;
};
