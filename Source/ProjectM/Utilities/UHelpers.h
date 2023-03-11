#pragma once
#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"


class PROJECTM_API UHelpers
{
public:
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"asset.Succeeded()");
		*OutObject = asset.Object;
	}

	template<typename T>
	static void CreateComponent(AActor* InActor, T** InComponent,
		FName InName, USceneComponent* InParent = NULL)
	{
		*InComponent = InActor->CreateDefaultSubobject<T>(InName);

		if (!!InParent)
		{
			(*InComponent)->SetupAttachment(InParent);
			return;
		}

		InActor->SetRootComponent((*InComponent));
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);

		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutClass = asset.Class;
	}


};
