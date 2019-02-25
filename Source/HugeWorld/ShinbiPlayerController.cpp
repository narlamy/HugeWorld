// Fill out your copyright notice in the Description page of Project Settings.

#include "ShinbiPlayerController.h"
#include "InputCoreTypes.h"
#include "Engine/EngineBaseTypes.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


void AShinbiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	
	if (InputComponent != nullptr)
	{
		//// Set up gameplay key bindings
		//check(InputComponent);
		InputComponent->BindAction("Jump", IE_Pressed, this, &AShinbiPlayerController::Jump);
		InputComponent->BindAction("Jump", IE_Released, this, &AShinbiPlayerController::StopJumping);

		InputComponent->BindAxis("MoveForward", this, &AShinbiPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &AShinbiPlayerController::MoveRight);

		//// We have 2 versions of the rotation bindings to handle different kinds of devices differently
		//// "turn" handles devices that provide an absolute delta, such as a mouse.
		//// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
		//InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		InputComponent->BindAxis("TurnRate", this, &AShinbiPlayerController::TurnAtRate);
		InputComponent->BindAxis("LookUp", this, &AShinbiPlayerController::AddControllerPitchInput);
		InputComponent->BindAxis("LookUpRate", this, &AShinbiPlayerController::LookUpAtRate);

		//// handle touch devices
		InputComponent->BindTouch(IE_Pressed, this, &AShinbiPlayerController::TouchStarted);
		InputComponent->BindTouch(IE_Released, this, &AShinbiPlayerController::TouchStopped);

		//// VR headset functionality
		//InputComponent->BindAction("ResetVR", IE_Pressed, this, &ASampleContorlCharacter::OnResetVR);
	}
}

//bool AShinbiPlayerController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
//{
//	return Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
//}


//void AShinbiPlayerController::OnResetVR()
//{
//	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
//}

void AShinbiPlayerController::Jump()
{
	dynamic_cast<ACharacter*>(GetPawn())->Jump();
}

void AShinbiPlayerController::StopJumping()
{
	dynamic_cast<ACharacter*>(GetPawn())->StopJumping();
}

void AShinbiPlayerController::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	dynamic_cast<ACharacter*>(GetPawn())->Jump();
}

void AShinbiPlayerController::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	dynamic_cast<ACharacter*>(GetPawn())->StopJumping();
}

void AShinbiPlayerController::AddControllerPitchInput(float Rate)
{
	GetPawn()->AddControllerPitchInput(Rate);
}

void AShinbiPlayerController::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	GetPawn()->AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AShinbiPlayerController::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	GetPawn()->AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void AShinbiPlayerController::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		auto pawn = GetPawn();

		/*auto pos = pawn->ActorToWorld().GetLocation();
		UE_LOG(LogTemp, Log, TEXT("MOVE: Forward ('%s') (X=%f, Y=%f, Z=%f)"), *pawn->GetName(), pos.X, pos.Y, pos.Z );*/

		// find out which way is forward
		const FRotator Rotation = this->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		pawn->AddMovementInput(Direction, Value);
	}
}

void AShinbiPlayerController::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		auto pawn = GetPawn();

		// find out which way is right
		const FRotator Rotation = this->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		pawn->AddMovementInput(Direction, Value);
	}
}