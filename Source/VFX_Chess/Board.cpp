// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create collider
	m_boardCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoardCollider"));
	RootComponent = m_boardCollider;
	m_boardCollider->InitBoxExtent(FVector(0, 0, 0));

	// Get square mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> squareMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	// Get mesh dimensions
	m_squareDimensions = squareMesh.Object->GetBounds().GetBox().GetSize();

	// Generate grid
	for (int i = 0; i < m_gridWidth * m_gridLength; ++i)
	{
		// Create a static mesh for each square
		m_grid.Add(CreateDefaultSubobject<UStaticMeshComponent>(*FString("Square_" + FString::FromInt(i))));
		m_grid[i]->SetupAttachment(m_boardCollider);

		// If square mesh exists
		if (squareMesh.Succeeded())
		{
			// Assign square mesh
			m_grid[i]->SetStaticMesh(squareMesh.Object);

			// Calculate (X, Y) position
			int xPos = (i / m_gridWidth) * m_squareDimensions.X;
			int yPos = (i % m_gridLength) * m_squareDimensions.Y;

			// Set position
			m_grid[i]->SetRelativeLocation(FVector(xPos, yPos, 0));
		}
	}
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

