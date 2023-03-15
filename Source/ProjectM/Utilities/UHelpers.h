#pragma once
#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"

//자주 사용되는 코드를 static 함수로 UHelpers class에 정의함
class PROJECTM_API UHelpers
{
public:

	//언리얼엔진의 에셋 레퍼런스 경로로 에셋을 할당한다
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"asset.Succeeded()");
		*OutObject = asset.Object;
	}

	//컴포넌트 생성 후 부모 컴포넌트(기본은 NULL) 혹은 루트 컴포넌트로 부착한다.
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

	//언리얼에서 생성한 블루프린트 객체의 레퍼런스 경로로 TSubClassOf<> 형태로 할당한다.
	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);

		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutClass = asset.Class;
	}


};
