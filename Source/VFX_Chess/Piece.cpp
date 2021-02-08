// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"

// Sets default values
APiece::APiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh
	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PieceMesh"));
	RootComponent = m_mesh;

	// Set light material
	static ConstructorHelpers::FObjectFinder<UMaterial> lightMaterial(TEXT("Material'/Game/Assets/Materials/Piece_Light.Piece_Light'"));
	if (lightMaterial.Object != NULL)
	{
		m_lightMaterial = (UMaterial*)lightMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Piece light material does not exist!"));
	}

	// Set dark material
	static ConstructorHelpers::FObjectFinder<UMaterial> darkMaterial(TEXT("Material'/Game/Assets/Materials/Piece_Dark.Piece_Dark'"));
	if (darkMaterial.Object != NULL)
	{
		m_darkMaterial = (UMaterial*)darkMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Piece dark material does not exist!"));
	}

	// Set selected material
	static ConstructorHelpers::FObjectFinder<UMaterial> selectedMaterial(TEXT("Material'/Game/Assets/Materials/Piece_Selected.Piece_Selected'"));
	if (selectedMaterial.Object != NULL)
	{
		m_selectedMaterial = (UMaterial*)selectedMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Selected material does not exist!"));
	}

	m_mesh->SetMaterial(0, m_lightMaterial);
}

// Called when the game starts or when spawned
/*void APiece::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

void APiece::SelectPiece()
{
	m_mesh->SetMaterial(0, m_selectedMaterial);
}

void APiece::DeselectPiece()
{
	if (m_isWhite)
	{
		m_mesh->SetMaterial(0, m_lightMaterial);
	}
	else
	{
		m_mesh->SetMaterial(0, m_darkMaterial);
	}
}

std::vector<int> APiece::CalculateMoves()
{
	UE_LOG(LogTemp, Warning, TEXT("Calculate Moves: Make call to specific piece."));
	return m_availableMoves;
}

void APiece::MovePiece(int _id, FVector _dimensions)
{
	UE_LOG(LogTemp, Warning, TEXT("Move Piece: Make call to specific piece."));
}