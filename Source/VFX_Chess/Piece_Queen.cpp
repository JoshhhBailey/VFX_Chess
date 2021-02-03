// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece_Queen.h"

APiece_Queen::APiece_Queen()
{
	// Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> queenMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (queenMesh.Succeeded())
	{
		m_mesh->SetStaticMesh(queenMesh.Object);

		// Get mesh dimensions
		SetDimensions(queenMesh.Object->GetBounds().GetBox().GetSize());
	}
}