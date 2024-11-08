// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	// Because this function is marked as 'BlueprintImplementableEvent', C++ doesn't expect us to write function body.
	// Unreal Engine expects us to to give the functionality in blueprints. But we can call it from C++.
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	// Time delay before Game starts
	float StartDelay = 3.f;

	void HandleGameStart();
};
