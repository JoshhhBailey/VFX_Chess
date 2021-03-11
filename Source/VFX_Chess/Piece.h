/// \file Piece.h
/// \brief Parent class for all pieces. Manages meshes, materials, skeletons etc...
/// \author Josh Bailey and Dmitrii Shevchenko
/// \date 09/03/21 Updated to NCCA Coding standard
/// Revision History:
///
/// \todo

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
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

	bool m_firstMove = true;

	void SetBlack();

	void SetDimensions(FVector _dimensions) { m_dimensions = _dimensions; }
	FVector GetDimensions() const { return m_dimensions; } 

	void SetSquareID(int _square) { m_square = _square; }
	int GetSquareID() { return m_square; }

	bool GetIsWhite() const { return m_isWhite; }

	void SelectPiece();
	void DeselectPiece();
	bool GetIsSelected() { return m_isSelected; }

	int GetID() const { return m_id; } 
	void SetID(int _id) { m_id = _id; }

	void SpawnBlueprint(FVector _dimensions, FRotator _rot);

	ACharacter* GetCharacter() const {return m_character;} 
	void SetCharacter(ACharacter* _character) {m_character = _character;};
	USkeletalMeshComponent*  GetSKMesh() const {if (m_character!=nullptr){return m_character->GetMesh();} else {return nullptr;}}
	void MovePiece(int _id, FVector _dimensions);

	// Overwritten by individual piece function
	virtual std::vector<std::vector<int>> CalculateMoves();
	virtual bool GetFirstMove();
	virtual void UpdateMaterial(); // Sets the correct material based on context

private:
	FVector m_dimensions;			// Dimensions of piece
	int m_square;							// The index of the square the piece is stood on
	bool m_isWhite = true;		// Colour of piece
	bool m_isSelected = false;
	int m_id;									// Position in active pieces vector
	ACharacter *m_character;

	

/*protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;*/
};
