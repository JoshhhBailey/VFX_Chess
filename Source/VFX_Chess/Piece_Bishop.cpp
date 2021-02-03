// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece_Bishop.h"

APiece_Bishop::APiece_Bishop()
{
	// Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> bishopMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (bishopMesh.Succeeded())
	{
		m_mesh->SetStaticMesh(bishopMesh.Object);
		m_mesh->SetRelativeScale3D({ 0.5f, 0.5f, 1.0f });

		// Get mesh dimensions
		SetDimensions(bishopMesh.Object->GetBounds().GetBox().GetSize());
	}
}