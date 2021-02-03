// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece_King.h"

APiece_King::APiece_King()
{
	// Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> kingMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (kingMesh.Succeeded())
	{
		m_mesh->SetStaticMesh(kingMesh.Object);
		m_mesh->SetRelativeScale3D({ 1.0f, 1.0f, 2.0f });

		// Get mesh dimensions
		SetDimensions(kingMesh.Object->GetBounds().GetBox().GetSize());
	}
}