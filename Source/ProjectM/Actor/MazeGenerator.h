#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

struct FCell {
	bool visited = false;
	bool walls[4] = { true, true,true,true };
};

UCLASS()
class PROJECTM_API AMazeGenerator : public AActor
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditAnywhere, Category = "Maze | Mesh")
	UHierarchicalInstancedStaticMeshComponent* InstancedMesh;


	UPROPERTY(EditAnywhere, Category = "Maze")
		int32 Seed;
	UPROPERTY(EditAnywhere, Category = "Maze | Size")
		float MeshSize;
	UPROPERTY(EditAnywhere, Category = "Maze | Size")
		FIntPoint Size;
	UPROPERTY(EditAnywhere, Category = "Maze | Location")
		FIntPoint StartLocation;
	UPROPERTY(VisibleAnywhere, Category = "Maze | Location")
		FIntPoint EndLocation;

	UPROPERTY(VisibleAnywhere, Category = "Maze")
		TSet<FIntPoint> PathTiles;
	TSet<FIntPoint> EndPaths;
	
public:	
	// Sets default values for this actor's properties
	AMazeGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:

	void GenerateMaze();
	void AddNeighbourLocation(FRandomStream& RandStream, FIntPoint& CurrLoc, TSet<FIntPoint>& BridgeTiles,
		TSet<FIntPoint>& ToCheck);
	void BackTrack(FIntPoint& CurrLoc, TSet<FIntPoint>& ToCheck,
		TSet<FIntPoint>& BridgeTiles);
	void CreateMeshInstance();

private:
	FORCEINLINE bool CheckIfLocExceedsSize(const FIntPoint& loc, const FIntPoint& size) 
	{ return(loc.X < 0 || loc.Y < 0 || size.X < loc.X || size.Y < loc.Y); }
	FORCEINLINE bool CheckIsValidLoc(const FIntPoint& loc, const FIntPoint& size,
		const TSet<FIntPoint>& BridgeTiles)
	{
		return !(CheckIfLocExceedsSize(loc, size) || PathTiles.Contains(loc) || BridgeTiles.Contains(loc));
	}

	//Distance == 2 : Floor Distance == 1 :Bridge
	FORCEINLINE FIntPoint GetNeibourLoc (const FIntPoint& Target,const int32 Distance, const int32 index){
		return TArray<FIntPoint> {
			FIntPoint(Target.X + Distance, Target.Y),
				FIntPoint(Target.X, Target.Y + Distance),
				FIntPoint(Target.X - Distance, Target.Y),
				FIntPoint(Target.X, Target.Y - Distance)
		}[index];
	};
	 TArray<FIntPoint> GetNeibourLoc(const FIntPoint& Target, const int32 Distance) {
		return TArray<FIntPoint> {
			FIntPoint(Target.X + Distance, Target.Y),
				FIntPoint(Target.X, Target.Y + Distance),
				FIntPoint(Target.X - Distance, Target.Y),
				FIntPoint(Target.X, Target.Y - Distance)
		};
	};
	int32 GetNeibourCount(const FIntPoint& CurrLoc);

};
