// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Board.generated.h"

UCLASS()
class VFX_CHESS_API ABoard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABoard();

	TArray<class UStaticMeshComponent*> m_grid;
	class UBoxComponent* m_boardCollider;

	// Materials
	UPROPERTY(EditAnywhere)
		class UMaterial* m_lightMaterial;
	UPROPERTY(EditAnywhere)
		class UMaterial* m_darkMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int m_gridWidth = 8;
	int m_gridLength = 8;
	FVector m_squareDimensions;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
