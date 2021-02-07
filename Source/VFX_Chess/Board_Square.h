// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board_Square.generated.h"

UCLASS()
class VFX_CHESS_API ABoard_Square : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard_Square();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* m_mesh;
	// Materials
	UPROPERTY(EditAnywhere)
		UMaterial* m_lightMaterial;
	UPROPERTY(EditAnywhere)
		UMaterial* m_darkMaterial;
	UPROPERTY(VisibleAnywhere)
		UMaterial* m_selectedMaterial;

	void SetLightMaterial() { m_mesh->SetMaterial(0, m_lightMaterial); }
	void SetDarkMaterial() { m_mesh->SetMaterial(0, m_darkMaterial); }
	void SetSelectedMaterial() { m_mesh->SetMaterial(0, m_selectedMaterial); }
	void ResetMaterial();
	FVector GetDimensions() { return m_dimensions; }

	void SetOccupied(bool _occupied) { m_occupied = _occupied; }
	bool GetOccupied() { return m_occupied; }

	void SetIsLightSquare(bool _bool) { m_isLightSquare = _bool; }

	void SetOccupiedPiece(class APiece* _occupiedPiece) { m_occupiedPiece = _occupiedPiece; }
	class APiece* GetOccupiedPiece() { return m_occupiedPiece; }
	void RemoveOccupiedPiece();

private:
	FVector m_dimensions;

	bool m_occupied;
	class APiece* m_occupiedPiece;

	bool m_isLightSquare = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
