// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMeshComponent -> SetupAttachment(CapsuleComponent);
	TurretMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMeshComponent -> SetupAttachment(BaseMeshComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint -> SetupAttachment(TurretMeshComponent);

}

void ABasePawn::HandleDestruction()
{
	//TODO: Visual/sound effects
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	//the vector from turret mesh to the coursor(target)
	FVector ToTarget = LookAtTarget - TurretMeshComponent->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMeshComponent -> SetWorldRotation(LookAtRotation);
	
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnPoint -> GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint -> GetComponentRotation();

	auto Projectile = GetWorld() -> SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile -> SetOwner(this);

}



