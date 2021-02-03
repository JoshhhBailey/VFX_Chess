// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece_Knight.h"

APiece_Knight::APiece_Knight()
{
	// Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> knightMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	if (knightMesh.Succeeded())
	{
		m_mesh->SetStaticMesh(knightMesh.Object);

		// Get mesh dimensions
		SetDimensions(knightMesh.Object->GetBounds().GetBox().GetSize());
	}
}