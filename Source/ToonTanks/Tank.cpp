// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	
	// Get the player controller
	auto playerController = Cast<APlayerController>(GetController());

	// Get the local player enhanced input subsystem
	auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	//Add the input mapping context
	eiSubsystem->AddMappingContext(inputMapping, 0);

	// Get the EnhancedInputComponent
	if(UEnhancedInputComponent* playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (inputMoveForward)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
				TEXT("...Action success..."));

			//BindAction for enhanced system takes Action, ETriggerEvent, object, and function
			//ETriggerEvent is an enum, where Triggered means "button is held down".
			playerEIcomponent->BindAction(inputMoveForward,
				ETriggerEvent::Triggered, this, &ATank::MoveForwardBackward);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
				TEXT("...Action failed..."));
		}
	}
}


void ATank::MoveForwardBackward(const FInputActionValue& Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = 2.f;
	AddActorLocalOffset(DeltaLocation);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Button pressed"));
}