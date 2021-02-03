// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
		class UMaterial* m_lightMaterial;
	UPROPERTY(VisibleAnywhere)
		class UMaterial* m_darkMaterial;

	void SetLight() { m_mesh->SetMaterial(0, m_lightMaterial); }
	void SetDark() { m_mesh->SetMaterial(0, m_darkMaterial); }

	void SetDimensions(FVector _dimensions) { m_dimensions = _dimensions; }
	FVector GetDimensions() { return m_dimensions; }

private:
	FVector m_dimensions;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
