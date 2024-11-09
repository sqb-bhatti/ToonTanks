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
		GameOver(false);  // send false because Player (Tank) dies
	}
	else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;

		if(TargetTowers == 0)
		{
			GameOver(true);  // send true because all Towers(enemies) dies
		}
	}
}


void AToonTanksGameMode::HandleGameStart()
{
	// Get the number of Towers (enemies) in the world
	TargetTowers = GetTargetTowerCount();
	
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


int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;

	// when this function executes, 'Towers' array will have all the Tower objects in the world
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	return Towers.Num();
}