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

	// Set light material
	static ConstructorHelpers::FObjectFinder<UMaterial> lightMaterial(TEXT("Material'/Game/Assets/Materials/Square_Light.Square_Light'"));
	if (lightMaterial.Object != NULL)
	{
		m_lightMaterial = (UMaterial*)lightMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Board light material does not exist!"));
	}

	// Set dark material
	static ConstructorHelpers::FObjectFinder<UMaterial> darkMaterial(TEXT("Material'/Game/Assets/Materials/Square_Dark.Square_Dark'"));
	if (darkMaterial.Object != NULL)
	{
		m_darkMaterial = (UMaterial*)darkMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Board dark material does not exist!"));
	}

	// Get square mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> squareMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	// If square mesh exists
	if (squareMesh.Succeeded())
	{
		// Get mesh dimensions
		m_squareDimensions = squareMesh.Object->GetBounds().GetBox().GetSize();

		// Generate grid - for each square
		for (int i = 0; i < m_gridWidth * m_gridLength; ++i)
		{
			// Create static mesh
			m_grid.Add(CreateDefaultSubobject<UStaticMeshComponent>(*FString("Square_" + FString::FromInt(i))));
			m_grid[i]->SetupAttachment(m_boardCollider);

			// Assign mesh
			m_grid[i]->SetStaticMesh(squareMesh.Object);

			// Assign material
			int materialA = (i / m_gridWidth) % 2;
			int materialB = (i % m_gridLength) % 2;
			bool selectedMaterial = XOR((bool)materialA, (bool)materialB);

			if (selectedMaterial)
			{
				m_grid[i]->SetMaterial(0, m_lightMaterial);
			}
			else
			{
				m_grid[i]->SetMaterial(0, m_darkMaterial);
			}

			// Set position
			int xPos = (i / m_gridWidth) * m_squareDimensions.X;
			int yPos = (i % m_gridLength) * m_squareDimensions.Y;
			m_grid[i]->SetRelativeLocation(FVector(xPos, yPos, 0));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("squareMesh does not exist!"));
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

