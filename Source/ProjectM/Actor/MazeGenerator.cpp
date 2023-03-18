#include "Actor/MazeGenerator.h"
#include "Global.h"

#include "Components/StaticMeshComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

// Sets default values
AMazeGenerator::AMazeGenerator()
	: MeshSize(100.f), Size(10.f,10.f),
	StartLocation(0,0) , EndLocation(0,0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UHelpers::CreateComponent(this, &InstancedMesh, "InstancedMesh");
	UStaticMesh* StaticMesh;
	UHelpers::GetAsset<UStaticMesh>(&StaticMesh, "StaticMesh'/Engine/BasicShapes/Cube.Cube'");
	InstancedMesh->SetStaticMesh(StaticMesh);

	/*UMaterialInstanceConstant* material;
	UHelpers::GetAsset<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Engine/BasicShapes/BasicShapeMaterial_Inst.BasicShapeMaterial_Inst'");

	InstancedMesh->SetMaterial(0,material);*/

}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//블루프린트에서는 호출하지 않아도 엔진이 처리한다.
	InstancedMesh->ClearInstances();

	PathTiles.Reset();
	EndPaths.Reset();

	GenerateMaze();
	CreateMeshInstance();
}

void AMazeGenerator::GenerateMaze()
{
	FRandomStream RandStream;
	RandStream.Initialize(Seed);

	TSet<FIntPoint> BridgeTiles;
	TSet<FIntPoint> ToCheck;
	FIntPoint CurrLoc = StartLocation;

	AddNeighbourLocation(RandStream, CurrLoc, BridgeTiles, ToCheck);
	while(ToCheck.Num() > 0)
	{
		CLog::Log(CurrLoc);
		CLog::Log(ToCheck.Num());
		BackTrack(CurrLoc, ToCheck, BridgeTiles);
		AddNeighbourLocation(RandStream, CurrLoc, BridgeTiles, ToCheck);
	}

}

void AMazeGenerator::BackTrack(FIntPoint& CurrLoc, TSet<FIntPoint>& ToCheck, TSet<FIntPoint>& BridgeTiles)
{
	//마지막 위치를 현재위치로 지정
	CurrLoc = ToCheck.Array().Last();
	ToCheck.Remove(CurrLoc);
	//마지막으로 추가된 거리1인 타일을 Bridge에서 Path로 넣기
	if (BridgeTiles.IsEmpty() == false) 
	{
		auto tile = BridgeTiles.Array().Last();
		PathTiles.Add(tile);
		BridgeTiles.Remove(tile);
	}
}

void AMazeGenerator::CreateMeshInstance()
{
	auto arr = PathTiles.Array();

	for (const FIntPoint& p : arr)
	{
		FTransform t{ FRotator::ZeroRotator, FVector(p.X * MeshSize, p.Y * MeshSize, 0.f),  FVector(1.f) };
		InstancedMesh->AddInstance(t);
	}
}

int32 AMazeGenerator::GetNeibourCount(const FIntPoint& CurrLoc)
{
	int32 cnt{};
	TArray<FIntPoint> arr = GetNeibourLoc(CurrLoc, 1);
	for (const auto& val : arr)
	{
		if (PathTiles.Contains(val)) cnt++;
	}
	
	return cnt;
}

void AMazeGenerator::AddNeighbourLocation(FRandomStream& RandStream, FIntPoint& CurrLoc, TSet<FIntPoint>& BridgeTiles, 
	TSet<FIntPoint>& ToCheck)
{
	int32 NeibourIndex = RandStream.RandRange(0, 3);

	int32 N = 4;
	int32 val = 0;
	while (val < N)
	{
		FIntPoint Floor = GetNeibourLoc(CurrLoc, 2, NeibourIndex);

		if (CheckIsValidLoc(Floor, Size, BridgeTiles))
		{
			Floor = GetNeibourLoc(CurrLoc, 2, NeibourIndex);
			
			PathTiles.Add(Floor);
			BridgeTiles.Add(GetNeibourLoc(CurrLoc, 1, NeibourIndex));
			ToCheck.Add(Floor);
			AddNeighbourLocation(RandStream, Floor, BridgeTiles, ToCheck);
		}
		else
		{
			if (val < N) {
				val++;

				NeibourIndex++;
				if (NeibourIndex >= 4) NeibourIndex = 0;
			}

		}
	}

	if (GetNeibourCount(CurrLoc) == 1) EndPaths.Add(CurrLoc);
	
}

