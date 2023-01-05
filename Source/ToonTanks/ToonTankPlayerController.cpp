// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankPlayerController.h"

void AToonTankPlayerController::SetplayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = bPlayerEnabled;
}