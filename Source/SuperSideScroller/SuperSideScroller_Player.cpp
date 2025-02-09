// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Player.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

ASuperSideScroller_Player::ASuperSideScroller_Player()
{
	//Set sprinting to false by default.
	bIsSprinting = false;
	//Set our Max Walk Speed to 300.0f
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ASuperSideScroller_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedPlayerInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedPlayerInput) {
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (EnhancedSubsystem) {
			EnhancedSubsystem->AddMappingContext(this->IC_Character, 0);
		}
		//Bind pressed action Sprint to your Sprint function
		EnhancedPlayerInput->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::Sprint);

		//Bind released action Sprint to your StopSprinting function
		EnhancedPlayerInput->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ASuperSideScroller_Player::StopSprinting);

		//Bind pressed action Throw to your ThrowProjectile function
		EnhancedPlayerInput->BindAction(IA_Throw, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::ThrowProjectile);

		EnhancedPlayerInput->BindAction(IA_ChaoLikesIt, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::ChaoLikesIt);
	}

}

#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

void ASuperSideScroller_Player::Sprint()
{
	if (!this->bIsSprinting) {
		UE_LOG(LogTemp, Warning, TEXT("Sprinting -> _>"));
		GLog->Flush();
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Yellow, TEXT("Sprinting -> _>"));
		}
		this->bIsSprinting = true;
		this->GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	}
}

void ASuperSideScroller_Player::StopSprinting()
{
	if (bIsSprinting) {
		UE_LOG(LogTemp, Warning, TEXT("Walking _-_-"));
		GLog->Flush();
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Yellow, TEXT("Walking _-_-"));
		}
		this->bIsSprinting = false;
		this->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}

void ASuperSideScroller_Player::ThrowProjectile()
{
    UE_LOG(LogTemp, Warning, TEXT("Projectile Thrown!!"));
	GLog->Flush();
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Cyan, TEXT("Projectile Thrown!!"));
	}
}

void ASuperSideScroller_Player::ChaoLikesIt()
{
	UE_LOG(LogTemp, Warning, TEXT("Chao Smiles ^_^")); 
	GLog->Flush();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Magenta, TEXT("Chao Smiles ^_^"));
	}

}
