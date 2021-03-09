///
///  @file Board.cpp
///  @brief Generation of entire board

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
		square->SetID(i);

		// Set position
		float xPos = (i % m_gridLength) * square->GetDimensions().X;
		float yPos = (i / m_gridWidth) * square->GetDimensions().Y;
		square->SetActorLocation({ xPos, yPos, 0.0f });

		// Set colour
		int materialA = (i / m_gridWidth) % 2;
		int materialB = (i % m_gridLength) % 2;
		bool selectedMaterial = XOR((bool)materialA, (bool)materialB);

		if (selectedMaterial)
		{
			square->SetDarkMaterial();
			square->SetIsLightSquare(false);
		}
		else
		{
			square->SetLightMaterial();
		}
		m_squares.push_back(square);
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

void ABoard::SetEnemyMaterial(int _index)
{
	m_squares[_index]->SetEnemyMaterial();
}

void ABoard::ResetMaterial(int _index)
{
	m_squares[_index]->ResetMaterial();
}