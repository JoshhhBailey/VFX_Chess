// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece_Rook.h"

APiece_Rook::APiece_Rook()
{
	// Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> rookMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (rookMesh.Succeeded())
	{
		m_mesh->SetStaticMesh(rookMesh.Object);
		m_mesh->SetRelativeScale3D({ 0.5f, 0.5f, 1.0f });

		// Get mesh dimensions
		SetDimensions(rookMesh.Object->GetBounds().GetBox().GetSize());
	}
}