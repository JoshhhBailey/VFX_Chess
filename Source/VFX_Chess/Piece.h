// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Piece.generated.h"

UCLASS()
class VFX_CHESS_API APiece : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APiece();

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* m_mesh;

	// Materials
	UPROPERTY(VisibleAnywhere)
		UMaterial* m_lightMaterial;
	UPROPERTY(VisibleAnywhere)
		UMaterial* m_darkMaterial;
	UPROPERTY(VisibleAnywhere)
		UMaterial* m_selectedMaterial;

	std::vector<std::vector<int>> m_availableMoves;		// ALL best case scenario possible moves for a piece

	void SetBlack() { m_mesh->SetMaterial(0, m_darkMaterial); m_isWhite = false; }

	void SetDimensions(FVector _dimensions) { m_dimensions = _dimensions; }
	FVector GetDimensions() { return m_dimensions; }

	void SetSquare(int _square) { m_square = _square; }
	int GetSquare() { return m_square; }

	bool GetIsWhite() { return m_isWhite; }

	void SelectPiece();
	void DeselectPiece();

	// Overwritten by individual piece function
	virtual std::vector<std::vector<int>> CalculateMoves();
	virtual void MovePiece(int _id, FVector _dimensions);

private:
	FVector m_dimensions;			// Dimensions of piece
	int m_square;							// The index of the square the piece is stood on
	bool m_isWhite = true;
	

/*protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;*/

};
