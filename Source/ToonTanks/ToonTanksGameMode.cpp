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
		GameOver(false);
	}else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		
		--TargetTowers;
		UE_LOG(LogTemp,Warning,TEXT("Quedan %i"),TargetTowers);
		if (TargetTowers==0)
		{
			GameOver(true);
		}
	}
	
}
void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> TowerList;
	UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),TowerList);
	
	return TowerList.Num();
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers=GetTargetTowerCount();

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
