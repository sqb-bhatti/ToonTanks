// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 1300.f;
	ProjectileMovement->MaxSpeed = 1300.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>("Smoke Trail");
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// 'AddDynamic' is the function we will use to bind our callback to 'OnComponentHit (multicast delegate)'
	// and add that function to it's invocation list
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				FVector NormalImpulse, const FHitResult& Hit)
{
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("On Hit"));
	
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}
	
	auto MyOwnerInstigator = MyOwner->GetInstigatorController();

	// If we want to get the UClass of any particular class such as UDamageType we call a function 'StaticClass()'
	auto DamageTypeClass = UDamageType::StaticClass();

	// Check Other actor is not equal to this Actor because we don't want damage to ourselves
	// Check other actor is not MyOwner because we don't want Projectile to cause damage to its owner
	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		// When we call this we will generate the damage event and 'OnTakeAnyDamage' delegate will broadcast
		// in response to this. And it means that in 'HealthComponent' the function 'DamageTaken' will gets
		// called
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);

		// Show the projectile hit particle
		if(HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles,
						GetActorLocation(), GetActorRotation());
		}
	}

	Destroy();  // Destroy the projectile after damage
}

