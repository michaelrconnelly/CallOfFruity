
#pragma once // Ensures the file is only included once during compilation

#include "CoreMinimal.h" // Core Unreal definitions and base types
#include "GameFramework/Character.h" // Gives access to ACharacter class
#include "CoFCharacter.generated.h" // Required for Unreal's reflection system (UCLASS, UPROPERTY, etc.)

// Declare a new class that inherits from ACharacter
UCLASS()
class CALLOFFRUITY_API ACoFCharacter : public ACharacter
{
	GENERATED_BODY() // Required macro that enables reflection and UE4 functionality

public:
	// Constructor - sets default values for this character's properties
	ACoFCharacter();

	// Called every frame (like Blueprint's Event Tick)
	virtual void Tick(float DeltaTime) override;

	// Called to bind input actions and axes to this character
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned (like Event BeginPlay)
	virtual void BeginPlay() override;

	// Custom input functions for movement and look controls
	void MoveForwardBackward(float Value);   // Forward/backward movement
	void MoveRightLeft(float Value);         // Left/right movement
	void TurnRightLeft(float Value);         // Camera yaw (turn left/right)
	void LookUpDown(float Value);            // Camera pitch (look up/down)

private:
	// SpringArm to hold the camera at a distance and allow smooth camera motion
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	// Actual camera that the player sees through
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

public:
	// Public section left here in case you want to add public variables or functions later
};
