// Fill out your copyright notice in the Description page of Project Settings.

#include "HugeWorldGameInstance.h"
#include "ShinbiPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"



//================================================================================
UHugeWorldGameInstance::UHugeWorldGameInstance()
{
	/* 
	[2019-02-26] narlamy
	static 변수 처럼 정의할 수도 있지만 특정 함수가 호출되면서
	아래처럼 함수를 호출해서 등록할 수도 있습니다.

	IConsoleManager::Get().RegisterConsoleVariable(TEXT("r.MoveSpeed"),
		100,
		TEXT("change character movment speed\n")
		TEXT("100 ~ 100000"),
		ECVF_Scalability | ECVF_RenderThreadSafe);
	*/
}