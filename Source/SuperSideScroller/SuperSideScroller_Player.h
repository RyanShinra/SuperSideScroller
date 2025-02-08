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

	void Sprint();
	void StopSprinting();

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* IC_Character = nullptr;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Sprint = nullptr;

private:
	bool bIsSprinting;
};