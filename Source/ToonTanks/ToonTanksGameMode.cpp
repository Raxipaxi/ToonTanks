// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "ToonTankPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDie(AActor* DeadActor)
{
	if (DeadActor==Tank)
	{
		Tank->HandleDestruction();
		if (TankPlayerController)
		{
			TankPlayerController->SetplayerEnabledState(false);
		}
	}else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}
void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
	
	
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	TankPlayerController =  Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	StartGame();
	if (TankPlayerController)
	{
		TankPlayerController->SetplayerEnabledState(false);
		FTimerHandle TimerHandle;
		FTimerDelegate TimerToStart = FTimerDelegate::CreateUObject(TankPlayerController,&AToonTankPlayerController::SetplayerEnabledState, true);
		GetWorldTimerManager().SetTimer(TimerHandle, TimerToStart,StartDelay,false );
	};

}
