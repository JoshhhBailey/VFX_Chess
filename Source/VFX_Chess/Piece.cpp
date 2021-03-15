///
///  @file Piece.cpp
///  @brief Parent class for all pieces. Manages meshes, materials, skeletons etc...

#include "Piece.h"
#include "GameFramework/Character.h"

// Sets default values
APiece::APiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh
	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PieceMesh"));
	RootComponent = m_mesh;

	// Set mesh shape
	static ConstructorHelpers::FObjectFinder<UStaticMesh> staticMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (staticMesh.Succeeded())
	{
		m_mesh->SetStaticMesh(staticMesh.Object);
		m_mesh->SetRelativeScale3D({0.5f, 0.5f, 1.0f});

		// Get mesh dimensions
		SetDimensions(staticMesh.Object->GetBounds().GetBox().GetSize());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to set static mesh!"));
	}

	// Set selected material
	static ConstructorHelpers::FObjectFinder<UMaterial> selectedMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Piece_Selected.Piece_Selected'"));
	if (selectedMaterial.Object != NULL)
	{
		m_selectedMaterial = (UMaterial *)selectedMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Selected material does not exist!"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> invisibleMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Piece_Invisible.Piece_Invisible'"));
	if (invisibleMaterial.Object != NULL)
	{
		m_invisibleMaterial = (UMaterial *)invisibleMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Piece dark material does not exist!"));
	}
	m_mesh->SetMaterial(0, m_invisibleMaterial);

	// Set collision properties
	m_mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	m_mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
/*void APiece::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

void APiece::SetBlack()
{
	m_isWhite = false;
	UpdateMaterial();
}

void APiece::SelectPiece()
{
	m_isSelected = true;
	UpdateMaterial();
}

void APiece::DeselectPiece()
{
	m_isSelected = false;
	UpdateMaterial();
}

void APiece::SpawnBlueprint(FVector _dimensions, FRotator _rot)
{
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	spawnParams.Owner = this;
	m_spawnedBlueprint = GetWorld()->SpawnActor<AActor>(m_pieceBlueprint, GetActorLocation(), _rot, spawnParams);
	m_character = Cast<ACharacter>(m_spawnedBlueprint);
	m_skeletalMesh = m_character->GetMesh();
	UpdateMaterial();
}

std::vector<std::vector<int>> APiece::CalculateMoves()
{
	UE_LOG(LogTemp, Warning, TEXT("Calculate Moves: Make call to specific piece."));
	return m_availableMoves;
}

void APiece::MovePiece(int _id, FVector _dimensions)
{
	if (m_firstMove)
	{
		m_firstMove = false;
	}

	float xPos = (_id % 8) * _dimensions.X;
	float yPos = (_id / 8) * _dimensions.Y;

	// Update location
	SetActorLocation({ xPos, yPos, GetActorLocation().Z});
	SetSquareID(_id);
	m_spawnedBlueprint->SetActorLocation({ xPos, yPos, m_spawnedBlueprint->GetActorLocation().Z});
}

bool APiece::GetFirstMove()
{
	return m_firstMove;
}

void APiece::UpdateMaterial()
{
	// Early return
	if (m_skeletalMesh == nullptr)
	{
		return;
	}

	UStaticMeshComponent* prop = Cast<UStaticMeshComponent>(m_skeletalMesh->GetChildComponent(0));
	if (prop != nullptr)
	{
		if (GetIsWhite())
		{
			prop->SetMaterial(0, m_propLightMaterial);
		}
		else
		{
			prop->SetMaterial(0, m_propDarkMaterial);
		}
	}

	UMaterial* resultMaterial;
	// Get correct material
	if (GetIsSelected())
	{
		resultMaterial = m_selectedMaterial;
		if (prop != nullptr)
		{
			prop->SetMaterial(0, m_selectedMaterial);
		}
	}
	else if (GetIsWhite())
	{
		resultMaterial = m_lightMaterial;
		if (prop != nullptr)
		{
				prop->SetMaterial(0, m_propLightMaterial);
		}
	}
	else
	{
		resultMaterial = m_darkMaterial;
		if (prop != nullptr)
		{
			prop->SetMaterial(0, m_propDarkMaterial);
		}
	}
	// Apply material
	for (int materialSlotIndex = 0; materialSlotIndex < m_skeletalMesh->GetNumMaterials(); materialSlotIndex++)
	{
		m_skeletalMesh->SetMaterial(materialSlotIndex, resultMaterial);
	}
}