// Fill out your copyright notice in the Description page of Project Settings.

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
	void MovePiece(int _id, FVector _dimensions);

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
