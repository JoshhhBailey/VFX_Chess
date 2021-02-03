// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Piece.h"

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
		class UStaticMeshComponent* m_squareMesh;
	UPROPERTY(EditAnywhere)
		class UMaterial* m_lightMaterial;
	UPROPERTY(EditAnywhere)
		class UMaterial* m_darkMaterial;

	void SetLightMaterial() { m_squareMesh->SetMaterial(0, m_lightMaterial); }
	void SetDarkMaterial() { m_squareMesh->SetMaterial(0, m_darkMaterial); }
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
