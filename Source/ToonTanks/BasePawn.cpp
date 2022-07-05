// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateEditorOnlyDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;
	BaseMeshComponent = CreateEditorOnlyDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMeshComponent -> SetupAttachment(CapsuleComponent);
	TurretMeshComponent = CreateEditorOnlyDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMeshComponent -> SetupAttachment(BaseMeshComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint -> SetupAttachment(TurretMeshComponent);

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	//the vector from turret mesh to the coursor(target)
	FVector ToTarget = LookAtTarget - TurretMeshComponent->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMeshComponent -> SetWorldRotation(LookAtRotation);
	
}



