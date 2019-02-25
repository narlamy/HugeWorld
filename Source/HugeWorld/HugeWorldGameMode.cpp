// Fill out your copyright notice in the Description page of Project Settings.

#include "HugeWorldGameMode.h"
#include "ShinbiPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"

AHugeWorldGameMode::AHugeWorldGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PawmFinder(TEXT("Blueprint'/Game/ParagonShinbi/Characters/Heroes/Shinbi/ShinbiPlayerCharacter.ShinbiPlayerCharacter_C'"));
	if (PawmFinder.Succeeded())
	{
		this->DefaultPawnClass = PawmFinder.Class;
	}	
	this->PlayerControllerClass = AShinbiPlayerController::StaticClass();
}