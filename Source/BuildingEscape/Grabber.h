// Created by Novoselov Vitaliy 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//
	UPROPERTY(EditAnywhere)
	float Reach = 100.0f;
	//
	UPhysicsHandleComponent* PhysicsHandler = nullptr;
	//
	UInputComponent* InputComponent = nullptr;
	
private:
	//
	void Grab();
	//
	void GrabReleased();
	// Find attached physics component
	void FindPhysicsController();
	// Setup input component
	void SetupInputComponent();
	// Return hit for physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;
	// Getting the players view point
	FVector GetReachLineEnd();
};