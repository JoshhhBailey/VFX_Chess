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
	UPROPERTY(VisibleAnyWhere)
		class USkeletalMeshComponent* m_skeletalMesh;

	// Materials
	UPROPERTY(VisibleAnywhere)
		UMaterial* m_lightMaterial;
	UPROPERTY(VisibleAnywhere)
		UMaterial* m_invisibleMaterial;
	UPROPERTY(VisibleAnywhere)
		UMaterial* m_darkMaterial;
	UPROPERTY(VisibleAnywhere)
		UMaterial* m_selectedMaterial;

	TSubclassOf<AActor> m_pieceBlueprint;
	AActor* m_spawnedBlueprint;

	APiece* m_parent;
	void SetParent(APiece* _parent) { m_parent = _parent; }
	APiece* GetParent() { return m_parent; }

	std::vector<std::vector<int>> m_availableMoves;		// ALL best case scenario possible moves for a piece

	bool m_firstMove;

	void SetBlack();

	void SetDimensions(FVector _dimensions) { m_dimensions = _dimensions; }
	FVector GetDimensions() { return m_dimensions; }

	void SetSquare(int _square) { m_square = _square; }
	int GetSquare() { return m_square; }

	bool GetIsWhite() { return m_isWhite; }

	void SelectPiece();
	void DeselectPiece();

	int GetID() { return m_id; }
	void SetID(int _id) { m_id = _id; }

	void SpawnBlueprint(FVector _dimensions, FRotator _orientation);

	// Overwritten by individual piece function
	virtual std::vector<std::vector<int>> CalculateMoves();
	virtual void MovePiece(int _id, FVector _dimensions);
	virtual bool GetFirstMove();

private:
	FVector m_dimensions;			// Dimensions of piece
	int m_square;							// The index of the square the piece is stood on
	bool m_isWhite = true;		// Colour of piece
	int m_id;									// Position in active pieces vector
	

/*protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;*/
};
