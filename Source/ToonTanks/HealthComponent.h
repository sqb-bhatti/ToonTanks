// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	float Health = 0.f;

	// Callback function
	// DamageType means in UE there are multiple types like fire damage, poison damage, fire damage
	// AController means the controller responsible for the damage
	// 'DamageCauser' this is the actual actor causing the damage (Projectile itself)

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
				AController* Instigator, AActor* DamageCauser);

	class AToonTanksGameMode* ToonTanksGameMode;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
