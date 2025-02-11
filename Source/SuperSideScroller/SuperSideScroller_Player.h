// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScrollerCharacter.h"
#include "SuperSideScroller_Player.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class SUPERSIDESCROLLER_API ASuperSideScroller_Player : public ASuperSideScrollerCharacter
{
	GENERATED_BODY()
	
	ASuperSideScroller_Player();

protected:
	// Override from base class
	//Override base character class function to set up our player input component
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Move(const FInputActionValue& Value) override;


	void OnStickPress();
	void OnRunButtonDown();
	void OnRunButtonUp();
    void OnThrowPressed();
	void ChaoLikesIt();
	
	//Input Mapping Context for our character
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* IC_Character = nullptr;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Sprint = nullptr;

	//Function to throw a projectile
    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* IA_Throw = nullptr;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* IA_ChaoLikesIt = nullptr;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_LeftStickPress = nullptr;

private:
	void StartRunning();
	void StopRunning();

private:
	//Boolean to check if we are sprinting
	bool bIsRunning = false;
	bool bWantsToRun = false;
	const float BaseWalkSpeed = 300.0f;
	const float RunSpeed = 500.0f;
};