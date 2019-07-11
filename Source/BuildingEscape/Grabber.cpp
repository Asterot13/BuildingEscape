// Created by Novoselov Vitaliy 2019

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	// Look for attached Physics Handle
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandler) 
	{
		// Physics handle is found

	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *(GetOwner()->GetName()));
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) 
	{
		// Bind Input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::GrabReleased);
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *(GetOwner()->GetName()));
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s Position: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// Draw a red trace in the world to visualize
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Red, false, 0.0f, 0.0f, 10.0f);

	// Setup query parameters
	FCollisionQueryParams TraceParameters (FName(TEXT("")), false, GetOwner());

	// Raycast out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
		);

	// See what we hit
	if(Hit.IsValidBlockingHit())
		UE_LOG(LogTemp, Warning, TEXT("Actor is: %s"), *Hit.GetActor()->GetName());
}

void UGrabber::Grab() 
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed!!!"));
}

void UGrabber::GrabReleased() 
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released!!!"));
}