// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"

// Sets default values
ABoard::ABoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();

	// Generate board
	for (int i = 0; i < m_gridWidth * m_gridLength; ++i)
	{
		// Spawn square
		ABoard_Square* square = GetWorld()->SpawnActor<ABoard_Square>(FVector(0, 0, 0), FRotator(0, 0, 0));
		m_squares.push_back(square);

		// Set position
		float xPos = (i % m_gridLength) * m_squares[i]->GetDimensions().X;
		float yPos = (i / m_gridWidth) * m_squares[i]->GetDimensions().Y;
		m_squares[i]->SetActorLocation({ xPos, yPos, 0.0f });

		// Set colour
		int materialA = (i / m_gridWidth) % 2;
		int materialB = (i % m_gridLength) % 2;
		bool selectedMaterial = XOR((bool)materialA, (bool)materialB);

		if (selectedMaterial)
		{
			m_squares[i]->SetLightMaterial();
		}
		else
		{
			m_squares[i]->SetDarkMaterial();
			m_squares[i]->SetIsLightSquare(false);
		}
	}

}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABoard::SetSelectedMaterial(int _index)
{
	m_squares[_index]->SetSelectedMaterial();
}

void ABoard::ResetMaterial(int _index)
{
	m_squares[_index]->ResetMaterial();
}