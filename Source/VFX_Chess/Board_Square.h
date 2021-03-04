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
	UPROPERTY(VisibleAnywhere)
		UMaterial* m_enemyMaterial;

	void SetLightMaterial() { m_mesh->SetMaterial(0, m_lightMaterial); }
	void SetDarkMaterial() { m_mesh->SetMaterial(0, m_darkMaterial); }
	void SetSelectedMaterial() { m_mesh->SetMaterial(0, m_selectedMaterial); }
	void SetEnemyMaterial() { m_mesh->SetMaterial(0, m_enemyMaterial); }
	void ResetMaterial();
	void SetDimensions(FVector _dimensions) { m_dimensions = _dimensions; }
	FVector GetDimensions() { return m_dimensions; }
	void SetScale(FVector _scale) { m_scale = _scale; }
	FVector GetScale() { return m_scale; }


	void SetID(int _id) { m_id = _id; }
	int GetID() { return m_id; }

	void SetIsLightSquare(bool _bool) { m_isLightSquare = _bool; }

	void SetOccupiedPiece(class APiece* _occupiedPiece) { m_occupiedPiece = _occupiedPiece; m_occupied = true; }
	void RemoveOccupiedPiece() { m_occupiedPiece = nullptr; m_occupied = false; }
	bool GetOccupied() { return m_occupied; }
	class APiece* GetOccupiedPiece() { return m_occupiedPiece; }

private:
	FVector m_dimensions;
	FVector m_scale;
	int m_id;

	bool m_occupied = false;
	class APiece* m_occupiedPiece = nullptr;

	bool m_isLightSquare = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
