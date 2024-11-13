// Fill out your copyright notice in the Description page of Project Settings.


#include "WanderingController.h"
#include "NavigationSystem.h"



// void AWanderingController::RandomMovement()
// {
// 	if(myNavSystem != nullptr)
// 	{
// 		if(GetPawn() != nullptr)
// 		{
// 			FNavLocation Result;
// 			if(myNavSystem->GetRandomReachablePointInRadius(GetPawn()->GetActorLocation(), 100, Result))
// 			{
// 				MoveToLocation(Result);
// 				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
// 		FString::Printf(TEXT("FNavLocation: %f"), Result.Location.Size()));
// 			}
// 			else
// 			{
// 				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
// 		FString::Printf(TEXT("myNavSystem is NULL")));
// 			}
// 		}
// 		else
// 		{
// 			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
// 				TEXT("GetPawn returned null"));
// 		}
// 	}
// 	else
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
// 				TEXT("RANDOM MOVEMENT FAILED, NAV SYSTEM NULL"));
// 	}
// }


// void AWanderingController::OnPossess(APawn* InPawn) {
// 	Super::OnPossess(InPawn);
//
// 	SetPawn(InPawn);
// 	myNavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
// }
//
//
// void AWanderingController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
// {
// 	Super::OnMoveCompleted(RequestID, Result);
//
// 	RandomMovement();
// }