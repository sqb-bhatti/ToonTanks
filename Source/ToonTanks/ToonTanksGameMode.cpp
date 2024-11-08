// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}


void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	// Check if the dead actor is the Tank
	if(DeadActor == Tank)
	{
		Tank->HandleDestruction();

		// Disable input for the Tank pawn
		if(ToonTanksPlayerController)
		{
			// Tank->DisableInput(Tank->GetTankPlayerController());
			// Tank->GetTankPlayerController()->bShowMouseCursor = false;  // Hide Mouse cursor as well
			
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
	}
	else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}


void AToonTanksGameMode::HandleGameStart()
{
	// We have a pointer to the Player Pawn in the form of a ATank pointer
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	ToonTanksPlayerController = Cast<AToonTanksPlayerController>
								(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	// Start a countdown timer after which we enable user input
	if(ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,
						&AToonTanksPlayerController::SetPlayerEnabledState, true);

		// Calling SetTimer using FTimerDelegate 
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate,
								StartDelay, false);
	}
}