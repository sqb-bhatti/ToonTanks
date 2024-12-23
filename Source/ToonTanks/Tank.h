// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	// getter function to get player controller
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool bAlive = true;  // check to see whether Tank is alive or dead

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 45.0f;

	//Setting up inputs. Mapping context and Input Action variables, to be set in Blueprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext * inputMapping = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction * inputMoveForward = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction * inputTurn = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction * inputRotateTurret = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction * inputFire = nullptr;
	

	APlayerController* TankPlayerController;
	
	// function which binds to Move forward axis mapping
	void MoveForwardBackward(const FInputActionValue & Value);

	void MoveLeftRight(const FInputActionValue & Value);
};
