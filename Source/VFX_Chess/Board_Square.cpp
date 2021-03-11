///
///  @file Board_Square.cpp
///  @brief Individual board square properties

#include "Board_Square.h"
#include "Piece.h"

// Sets default values
ABoard_Square::ABoard_Square()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh
	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardSquareMesh"));
	RootComponent = m_mesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> squareMesh(TEXT("StaticMesh'/Game/VFX_Chess/Assets/Board/square_scaled_down.square_scaled_down'"));
	m_mesh->SetStaticMesh(squareMesh.Object);

	// Get mesh dimensions and scale
	m_mesh->SetRelativeScale3D({ 1.0f, 1.0f, 1.0f });
	SetScale(m_mesh->GetRelativeScale3D());
	SetDimensions(squareMesh.Object->GetBounds().GetBox().GetSize() * GetScale());

	// Set light material
	static ConstructorHelpers::FObjectFinder<UMaterial> lightMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Board/squareLight_MAT.squareLight_MAT'"));
	if (lightMaterial.Object != NULL)
	{
		m_lightMaterial = (UMaterial*)lightMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Board light material does not exist!"));
	}

	// Set dark material
	static ConstructorHelpers::FObjectFinder<UMaterial> darkMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Board/squareDark_MAT.squareDark_MAT'"));
	if (darkMaterial.Object != NULL)
	{
		m_darkMaterial = (UMaterial*)darkMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Board dark material does not exist!"));
	}

	// Set selected material
	static ConstructorHelpers::FObjectFinder<UMaterial> selectedMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Available_Moves.Available_Moves'"));
	if (selectedMaterial.Object != NULL)
	{
		m_selectedMaterial = (UMaterial*)selectedMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Selected material does not exist!"));
	}

	// Set enemy material
	static ConstructorHelpers::FObjectFinder<UMaterial> enemyMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Piece_Enemy.Piece_Enemy'"));
	if (enemyMaterial.Object != NULL)
	{
		m_enemyMaterial = (UMaterial*)enemyMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy material does not exist!"));
	}
}

// Called when the game starts or when spawned
void ABoard_Square::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoard_Square::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoard_Square::ResetMaterial()
{
	if (m_isLightSquare)
	{
		m_mesh->SetMaterial(0, m_lightMaterial);
	}
	else
	{
		m_mesh->SetMaterial(0, m_darkMaterial);
	}
}