// Fill out your copyright notice in the Description page of Project Settings.


#include "BRCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABRCharacter::ABRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// mouse rates
	horizontalRate = 100.0f;
	veritcalRate = 100.0f;

	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	JumpMaxCount = 2;

	// Create a first person component
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));	// Attach the camera component to our capsule component
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));							// Position the camera slightly above the eyes
	FPSCameraComponent->bUsePawnControlRotation = true;																// Enable the pawn to control the camera rotation
}

// Called when the game starts or when spawned
void ABRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Log message
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Here comes the BRCharacter"));
}

// Called every frame
void ABRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Movement", this, &ABRCharacter::Movement);
	PlayerInputComponent->BindAxis("Strafe", this, &ABRCharacter::Strafing);
	PlayerInputComponent->BindAxis("Turn", this, &ABRCharacter::Turn);
	PlayerInputComponent->BindAxis("Lookup", this, &ABRCharacter::Lookup);
	PlayerInputComponent->BindAction("Sprint",IE_Pressed, this, &ABRCharacter::SprintWalk);   // The sprint is toggled
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABRCharacter::JumpOrNot);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABRCharacter::JumpOrNot);
}

// Implementing the forward and backward movement of the player
void ABRCharacter::Movement(float val) {
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(direction, val);
}

// Implement the left and right strafing of the player
void ABRCharacter::Strafing(float val) {
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(direction, val);
}

void ABRCharacter::Turn(float val) {
	AddControllerYawInput(val * horizontalRate * GetWorld()->GetDeltaSeconds());
}

void ABRCharacter::Lookup(float val) {
	AddControllerPitchInput(val * veritcalRate * GetWorld()->GetDeltaSeconds());
}

// Implement Running
void ABRCharacter::SprintWalk() {
	if (isSprint) {
		GetCharacterMovement()->MaxWalkSpeed = walk;
		isSprint = false;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = sprint;
		isSprint = true;
	}
}

void ABRCharacter::JumpOrNot() {
	if (bPressedJump) {
		bPressedJump = false;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Jump - %d"), JumpCurrentCount));
	}
	else {
		bPressedJump = true;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Jump - %d"), JumpCurrentCount));
		if (JumpCurrentCount == JumpMaxCount) {
			JumpCurrentCount++;  // Cancels additional jump. Maybe let the player to add more jumps
			LaunchCharacter(FVector(0.0f, 0.0f, jumpBoost), false, true);
		}
	}
}

// I want to implement dash maybe as a special skill
void ABRCharacter::Dash() {
	if (isSprint && dashTimer == 0.0f) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Go Dasher!"));
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * dashBoost;
	}
}

