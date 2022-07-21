// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm -> SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera component"));
    Camera -> SetupAttachment(SpringArm);
}



void ATank:: SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent -> BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent -> BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController -> GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}
void ATank::BeginPlay()
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());

    //DrawDebugSphere(GetWorld(), GetActorLocation() + FVector(0.f,0.f,200.f), 100.f, 12, FColor::Red, true, 30.f);
}
void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    //X = Value * DelyaTime * Speed
    DeltaLocation.X = Value * DeltaTime * Speed;
    AddActorLocalOffset(DeltaLocation,true);

}

void ATank::Turn(float Value)
{
    FRotator DeltaRotator = FRotator::ZeroRotator;
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaRotator.Yaw = Value * DeltaTime * TurnRate;
    AddActorLocalRotation(DeltaRotator, true);
 }
 
