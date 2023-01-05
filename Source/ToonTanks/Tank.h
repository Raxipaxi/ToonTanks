// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	ATank();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;

	APlayerController* GetPlayerController() const {return PlayerControllerPtr;}
private:

	UPROPERTY(EditInstanceOnly,BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess="true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditInstanceOnly,BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess="true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditInstanceOnly,BlueprintReadWrite, Category="Stats", meta = (AllowPrivateAccess="true"))
	float Speed = 200.f;

	UPROPERTY(EditInstanceOnly,BlueprintReadWrite, Category="Stats", meta = (AllowPrivateAccess="true"))
	float TurnRate = 20.f;

//  Movement
	void Move(float Value);
	void Turn(float Value);

	APlayerController* PlayerControllerPtr;

	

	
};
