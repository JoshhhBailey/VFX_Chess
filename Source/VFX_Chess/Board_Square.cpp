// Fill out your copyright notice in the Description page of Project Settings.


#include "Board_Square.h"

// Sets default values
ABoard_Square::ABoard_Square()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh
	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PieceMesh"));
	RootComponent = m_mesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> squareMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	m_mesh->SetStaticMesh(squareMesh.Object);

	// Get mesh dimensions
	m_dimensions = squareMesh.Object->GetBounds().GetBox().GetSize();

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
}

// Called when the game starts or when spawned
void ABoard_Square::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoard_Square::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoard_Square::RemoveOccupiedPiece()
{
	if (m_occupiedPiece != nullptr && m_occupied)
	{
		m_occupiedPiece = nullptr;
		m_occupied = false;
	}
}