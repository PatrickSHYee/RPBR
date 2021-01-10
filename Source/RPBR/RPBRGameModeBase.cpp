// Copyright Epic Games, Inc. All Rights Reserved.


#include "RPBRGameModeBase.h"

ARPBRGameModeBase::ARPBRGameModeBase() {

}

void ARPBRGameModeBase::StartPlay()
{
	Super::StartPlay();

	// Add logging messaging for verifying and debugging code during development.
	check(GEngine != nullptr);
	
	// Display a debug message for 5 seconds. The -1 "Key" value argument prevents the message from being updated or refreshed
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Hello Player, this is Hero X"));

}
