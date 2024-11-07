// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	// We have a pointer to the Player Pawn in the form of a ATank pointer
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}


void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	// Check if the dead actor is the Tank
	if(DeadActor == Tank)
	{
		Tank->HandleDestruction();

		// Disable input for the Tank pawn
		if(Tank->GetTankPlayerController())
		{
			Tank->DisableInput(Tank->GetTankPlayerController());
			Tank->GetTankPlayerController()->bShowMouseCursor = false;  // Hide Mouse cursor as well
		}
	} else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}