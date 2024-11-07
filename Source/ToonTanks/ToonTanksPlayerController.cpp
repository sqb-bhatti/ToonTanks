// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"


// Set the player state enabled/disabled (whether player can take the input that will move tha Tank)
void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if(bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	} else
	{
		GetPawn()->DisableInput(this);
	}

	// So the player controller has that 'bShowMouseCursor' as well and we have to set that as well
	bShowMouseCursor = bPlayerEnabled;
}