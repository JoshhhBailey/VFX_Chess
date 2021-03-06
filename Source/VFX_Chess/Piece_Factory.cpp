// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece_Factory.h"

// Sets default values
APiece_Factory::APiece_Factory(ABoard* _board)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_board = _board;
	m_squareSize = m_board->m_squares[0]->GetDimensions();
}

// Called when the game starts or when spawned
void APiece_Factory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APiece_Factory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

APiece* APiece_Factory::CreatePawn(int _id, bool _isWhite)
{
	if (_isWhite)
	{
		m_squareIDoffset = 8;
		m_yPos = 1;
		m_rot = { 0, 90, 0 };
	}
	else
	{
		m_squareIDoffset = 48;
		m_yPos = 6;
		m_rot = { 0, -90, 0 };
	}
	m_pos = { m_squareSize.X * _id, m_squareSize.Y * m_yPos, 50.0f };

	APiece_Pawn* piece = GetWorld()->SpawnActor<APiece_Pawn>(FVector::ZeroVector, FRotator::ZeroRotator);	// Change to deffered
	if (!_isWhite)
	{
		piece->SetBlack();
	}
	piece->SetID(_id);
	piece->SetSquareID(m_squareIDoffset + _id);
	// UGameplayStatics::FinishSpawningActor(pawn_instance, SpawnTransform);
	piece->SetActorLocation(m_pos);
	m_board->m_squares[m_squareID]->SetOccupiedPiece(piece);
	piece->SpawnBlueprint(m_squareSize, m_rot);
	return piece;
}

APiece* APiece_Factory::CreateOtherPiece(std::string _name, bool _isWhite)
{
	// Initialise piece
	m_class = m_class_MAP.at(_name);
	m_pieceID = m_pieceID_MAP.at(_name);
	m_squareID = m_squareID_MAP.at(_name)[_isWhite];
	m_xPos = m_xPos_MAP.at(_name);

	// Set blueprint rotation
	if (_isWhite)
	{
		m_yPos = 0;
		m_rot = { 0, 90, 0 };
	}
	else
	{
		m_yPos = 7;
		m_rot = { 0, -90, 0 };
	}
	m_pos = { m_squareSize.X * m_xPos, m_squareSize.Y * m_yPos, 50.0f };

	// Create piece
	APiece* piece = GetWorld()->SpawnActor<m_class>(FVector::ZeroVector, FRotator::ZeroRotator);	// Change to deffered
	if (!_isWhite)
	{
		piece->SetBlack();
	}
	piece->SetID(m_pieceID);
	piece->SetSquareID(m_squareID);
	// UGameplayStatics::FinishSpawningActor(pawn_instance, SpawnTransform);
	piece->SetActorLocation(m_pos);
	m_board->m_squares[m_squareID]->SetOccupiedPiece(piece);
	piece->SpawnBlueprint(m_squareSize, m_rot);
	return piece;
}