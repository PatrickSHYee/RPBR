// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "BRCharacter.generated.h"

UCLASS()
class RPBR_API ABRCharacter : public ACharacter
{
	GENERATED_BODY()

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UCharacterMovementComponent* char_Movement;*/

public:
	// Sets default values for this character's properties
	ABRCharacter();

	// mouse variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mouse)
	float veritcalRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mouse)
	float horizontalRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Jump)
	float jumpBoost = 550.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Dash)
	float dashBoost = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Dash)
	float dashTime = 1.5f;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles the input for forward and backward movement
	UFUNCTION()
		void Movement(float val);

	// Handles the input for the left and right strafing
	UFUNCTION()
		void Strafing(float val);

	// Turn and Look up
	UFUNCTION()
		void Turn(float val);
	UFUNCTION()
		void Lookup(float val);

	// Handles the input for sprint
	UFUNCTION()
		void SprintWalk();

	// Handles the jumping
	UFUNCTION()
		void JumpOrNot();

	void Dash();

private:
	bool isSprint = false;
	float walk = 600.0f;
	float sprint = 2000.0f;
	float dashTimer = 0.0f;
};
