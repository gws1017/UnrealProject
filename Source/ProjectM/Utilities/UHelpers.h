#pragma once
#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"

//���� ���Ǵ� �ڵ带 static �Լ��� UHelpers class�� ������
class PROJECTM_API UHelpers
{
public:

	//�𸮾����� ���� ���۷��� ��η� ������ �Ҵ��Ѵ�
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"asset.Succeeded()");
		*OutObject = asset.Object;
	}

	//������Ʈ ���� �� �θ� ������Ʈ(�⺻�� NULL) Ȥ�� ��Ʈ ������Ʈ�� �����Ѵ�.
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

	//�𸮾󿡼� ������ �������Ʈ ��ü�� ���۷��� ��η� TSubClassOf<> ���·� �Ҵ��Ѵ�.
	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);

		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutClass = asset.Class;
	}


};
