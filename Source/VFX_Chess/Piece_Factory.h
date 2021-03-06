// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Board.h"
#include "Piece.h"
#include "Piece_Pawn.h"
#include "Piece_Rook.h"
#include "Piece_Bishop.h"
#include "Piece_Knight.h"
#include "Piece_Queen.h"
#include "Piece_King.h"

#include <map>
#include <string>
#include <vector>

#include "Piece_Factory.generated.h"

UCLASS()
class VFX_CHESS_API APiece_Factory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APiece_Factory(ABoard* _board);

private:
	// Board
	ABoard* m_board;
	FVector m_squareSize;

	APiece* m_class;
	int m_pieceID;
	int m_squareID;
	int m_xPos;
	int m_yPos;
	FVector m_pos;
	FRotator m_rot;
	int m_squareIDoffset; // Pawn specific

	// Name : APiece class type
	std::map<std::string, APiece*> m_class_MAP = { {"Knight1" , &APiece_Knight()},
																								 {"Knight2" , &APiece_Knight()},
																								 {"Bishop1" , &APiece_Bishop()},
																								 {"Bishop2" , &APiece_Bishop()},
																								 {"Rook1"	  , &APiece_Rook()  },
																								 {"Rook2"	  , &APiece_Rook()  },
																								 {"Queen"   , &APiece_Queen() },
																								 {"King"    , &APiece_King()	} };

	// Name : Piece ID
	std::map<std::string, int> m_pieceID_MAP = { {"Knight1" , 10},
																							 {"Knight2" , 11},
																							 {"Bishop1" , 12},
																							 {"Bishop2" , 13},
																							 {"Rook1"	  ,  8},
																							 {"Rook2"	  ,  9},
																							 {"Queen"   , 14},
																							 {"King"    , 15} };

	// Name : Square ID [white, black]
	std::map<std::string, std::vector<int>> m_squareID_MAP = { {"Knight1" , {6, 62}},
																														 {"Knight2" , {1, 57}},
																														 {"Bishop1" , {5, 61}},
																														 {"Bishop2" , {2, 58}},
																														 {"Rook1"	  , {7, 63}},
																														 {"Rook2"	  , {0, 56}},
																														 {"Queen"   , {4, 60}},
																														 {"King"    , {3, 59}} };

	// Name : Grid x pos
	std::map<std::string, int> m_xPos_MAP = { {"Knight1" , 6},
																						{"Knight2" , 1},
																						{"Bishop1" , 5},
																						{"Bishop2" , 2},
																						{"Rook1"	 , 7},
																						{"Rook2"	 , 0},
																						{"Queen"   , 4},
																						{"King"    , 3} };


	APiece* CreatePawn(int _id, bool _isWhite);
	APiece* CreateOtherPiece(std::string _name, bool _isWhite);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
