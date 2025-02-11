// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Player.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
// May Not Need
#include "Engine/Engine.h" 
#include "GameFramework/PlayerController.h"

ASuperSideScroller_Player::ASuperSideScroller_Player()
{
    //Set sprinting to false by default.
    bIsRunning = false;
    //Set our Max Walk Speed to 300.0f
	GetCharacterMovement()->MaxWalkSpeed = this->BaseWalkSpeed;
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
		//Bind pressed action Sprint Triggered to OnRunButtonDown function
		EnhancedPlayerInput->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::OnRunButtonDown);

		//Bind released action Sprint Completed to OnRunButtonUp function
		EnhancedPlayerInput->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ASuperSideScroller_Player::OnRunButtonUp);

		//Bind pressed action Throw Triggered to OnThrowPressed function
		EnhancedPlayerInput->BindAction(IA_Throw, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::OnThrowPressed);

		EnhancedPlayerInput->BindAction(IA_ChaoLikesIt, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::ChaoLikesIt);

		//Bind the stick press
		EnhancedPlayerInput->BindAction(IA_LeftStickPress, ETriggerEvent::Started, this, &ASuperSideScroller_Player::OnStickPress);
	}

}

void ASuperSideScroller_Player::Move(const FInputActionValue& Value)
{
	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(-1, 0.18f, FColor::Silver, TEXT("Child Move Fn"));
	//}

	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (MovementVector.Size() > 0.0f)
	{
		if (bWantsToRun && !bIsRunning)
		{
			StartRunning();
		}
		else if (!bWantsToRun && bIsRunning)
		{
			StopRunning();
		}
	}
	else
	{
		if(bIsRunning) StopRunning();
	}

	Super::Move(Value);
}



void ASuperSideScroller_Player::OnStickPress()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green, TEXT("Child OnStickPress Fn"));
	}

	// Toggle the running state
	bWantsToRun = !bWantsToRun;

	//// If we're currently moving, start running immediately
	//if (GetVelocity().Size2D() > 0.0f)
	//{
	//	bIsRunning = bWantsToRun;
	//	UpdateMovementSpeed();
	//}
}

void ASuperSideScroller_Player::OnRunButtonDown()
{
	if (GEngine) {
		//GEngine->AddOnScreenDebugMessage(-1, 0.18f, FColor::Green, TEXT("Child OnRunButtonDown Fn"));
	}
	bWantsToRun = true;
}

void ASuperSideScroller_Player::OnRunButtonUp()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green, TEXT("Child OnRunButtonUp Fn"));
	}
	bWantsToRun = false;
}

void ASuperSideScroller_Player::OnThrowPressed()
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

void ASuperSideScroller_Player::StartRunning()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Yellow, TEXT("Running -> ->"));
	}
	this->bIsRunning = true;
	this->GetCharacterMovement()->MaxWalkSpeed = this->RunSpeed;
}

void ASuperSideScroller_Player::StopRunning()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Yellow, TEXT("Walking _-_-"));
	}
	this->bIsRunning = false;
	this->GetCharacterMovement()->MaxWalkSpeed = this->BaseWalkSpeed;
}
