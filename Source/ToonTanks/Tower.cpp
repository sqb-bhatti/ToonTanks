// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank)
	{
		// find the distance between Tower and the Tank. 1st parameter is current object 'Tower' and 2nd is 'Tank'
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		// check to see if Tank is in range
		if (Distance <= FireRange)
		{
			// If in range, rotate turret towards Tank
			RotateTurret(Tank->GetActorLocation());
		}
	}
}


void ATower::BeginPlay()
{
	Super::BeginPlay();

	// Get a reference to the Tank
	// PlayerIndex is set to 0 because single player games like this always have a player index is 0
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}