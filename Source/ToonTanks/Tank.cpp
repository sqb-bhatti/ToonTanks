// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
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

		if (inputTurn)
		{
			playerEIcomponent->BindAction(inputTurn,
				ETriggerEvent::Triggered, this, &ATank::MoveLeftRight);
		}

		if (inputFire)
		{
			// Bind Fire action
			// playerEIcomponent->BindAction(inputFire, IE_Pressed, this, &ATank::Fire);
			playerEIcomponent->BindAction(inputFire, ETriggerEvent::Triggered, this, &ATank::Fire);
		}
	}
}


void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false,
			HitResult);

		DrawDebugSphere(
		GetWorld(),  // returns a pointer to our current world
		HitResult.ImpactPoint,
		25.f,
		12,
		FColor::Red,
		false,
		-1.f);

		RotateTurret(HitResult.ImpactPoint);
	}
}


void ATank::MoveForwardBackward(const FInputActionValue& Value)
{
	FVector DeltaLocation = Value.Get<FVector>();

	// X = Value * DeltaTime * Speed  (Move tank using Delta time)
	DeltaLocation.X = Value[1] * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation);

	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Forward/Backward"));
}


void ATank::MoveLeftRight(const FInputActionValue & Value)
{
	float TurnValue = Value.Get<float>();
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = Value[1] * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(NewRotation, true);

	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Left/Right"));
}


void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	// In case of Tank, we are not destroying Tank, we will hide and disable ticking of Tank
	SetActorHiddenInGame(true);  // Hide the Tank
	SetActorTickEnabled(false);  // Disable ticking for the Tank
	bAlive = false;
}