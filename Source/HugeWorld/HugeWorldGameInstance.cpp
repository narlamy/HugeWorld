// Fill out your copyright notice in the Description page of Project Settings.

#include "HugeWorldGameInstance.h"
#include "ShinbiPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

//================================================================================
// �ܼ� ���� (Console variables)
//================================================================================
static TAutoConsoleVariable<float> CVarRefractionQuality(
	TEXT("MoveSpeed"),
	1000,
	TEXT("Change character movement speed\n")
	TEXT("range : [200, 500000]"),
	ECVF_Scalability | ECVF_RenderThreadSafe);

//================================================================================
UHugeWorldGameInstance::UHugeWorldGameInstance()
{
	/* 
	[2019-02-26] narlamy
	static ���� ó�� ������ ���� ������ Ư�� �Լ��� ȣ��Ǹ鼭
	�Ʒ�ó�� �Լ��� ȣ���ؼ� ����� ���� �ֽ��ϴ�.

	IConsoleManager::Get().RegisterConsoleVariable(TEXT("r.MoveSpeed"),
		100,
		TEXT("change character movment speed\n")
		TEXT("100 ~ 100000"),
		ECVF_Scalability | ECVF_RenderThreadSafe);
	*/
}