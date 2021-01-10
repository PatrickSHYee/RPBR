// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicProjectile.h"

// Sets default values
ABasicProjectile::ABasicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	// Set up for the projectile's collision component
	if (!CollisionComponent) {
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));				// Using a sphere as a simple collision representation
		CollisionComponent->InitSphereRadius(15.0f);														// Set the sphere's collision radius
		RootComponent = CollisionComponent;																	// Set the root component to be the collision component
	}

	// Set up the projectile's movement component
	if (!ProjMoveComponent) {
		ProjMoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjMoveComponent->SetUpdatedComponent(CollisionComponent);											// Applying the Collision component to the projectile movement component
		ProjMoveComponent->InitialSpeed = 3000.0f;
		ProjMoveComponent->MaxSpeed = 3000.0f;
		ProjMoveComponent->bRotationFollowsVelocity = true;
		ProjMoveComponent->Bounciness = 0.3f;
		ProjMoveComponent->ProjectileGravityScale = 0.0f;
	}
}

// Called when the game starts or when spawned
void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Projectile's velocity in the shooting direction
void ABasicProjectile::FireInDirection(const FVector& direction) {
	ProjMoveComponent->Velocity = direction * ProjMoveComponent->InitialSpeed;
}

