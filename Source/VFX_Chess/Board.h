// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Board_Square.h"
#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

UCLASS()
class VFX_CHESS_API ABoard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABoard();

	std::vector<ABoard_Square*> m_squares;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int m_gridWidth = 8;
	int m_gridLength = 8;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
