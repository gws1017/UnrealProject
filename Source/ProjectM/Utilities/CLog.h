#pragma once
#include "CoreMinimal.h"
#define PrintLine(){CLog::Log(__FUNCTION__,__LINE__);}

class PROJECTM_API CLog
{
public:
	//화면에서 보여질 메세지
	static void Print(int64 InValue, int32 InKey = -1, float Duration = 10.f, FColor InColor = FColor::Blue);
	static void Print(int32 InValue, int32 InKey = -1, float Duration = 10.f, FColor InColor = FColor::Blue);
	static void Print(float InValue, int32 InKey = -1, float Duration = 10.f, FColor InColor = FColor::Blue);
	static void Print(const FString& InValue, int32 InKey = -1, float Duration = 10.f, FColor InColor = FColor::Blue);
	static void Print(const FVector& InValue, int32 InKey = -1, float Duration = 10.f, FColor InColor = FColor::Blue);
	static void Print(const FRotator& InValue, int32 InKey = -1, float Duration = 10.f, FColor InColor = FColor::Blue);

	static void Log(int32 InValue);
	static void Log(float InValue);
	static void Log(const FString& InValue);
	static void Log(const FVector& InValue);
	static void Log(const FRotator& InValue);
	static void Log(const FIntPoint& InValue);

	static void Log(const UObject* InObject);
	static void Log(const FString& InFuncName, int32 InlineNumber);
};
