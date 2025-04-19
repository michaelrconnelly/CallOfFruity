
#include "CoFCharacter.h" // Includes the header file for this class
#include "GameFramework/SpringArmComponent.h" // Needed for the SpringArm component
#include "Camera/CameraComponent.h" // Needed for the Camera component

// Constructor - sets default values
ACoFCharacter::ACoFCharacter()
{
	PrimaryActorTick.bCanEverTick = true; // Enables the Tick function to run every frame

	// Create a SpringArm component and attach it to the character mesh
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh()); // Attach the boom to the character's mesh
	CameraBoom->TargetArmLength = 400.f; // Set how far the camera follows behind
	CameraBoom->bUsePawnControlRotation = true; // Rotate boom based on controller input

	// Create a Camera component and attach it to the end of the boom
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach to boom end
	FollowCamera->bUsePawnControlRotation = false; // Don't rotate camera with controller
}

// Called when the game starts or actor is spawned
void ACoFCharacter::BeginPlay()
{
	Super::BeginPlay(); // Call the base class BeginPlay
}

// Binds input actions and axes to functions
void ACoFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); // Call base class input setup

	// Bind "Jump" action to ACharacter's Jump function
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	// Bind movement axes to your custom movement functions
	PlayerInputComponent->BindAxis("MoveForwardBackward", this, &ACoFCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveRightLeft", this, &ACoFCharacter::MoveRightLeft);
	PlayerInputComponent->BindAxis("TurnRightLeft", this, &ACoFCharacter::TurnRightLeft);
	PlayerInputComponent->BindAxis("LookUpDown", this, &ACoFCharacter::LookUpDown);
}

// Handles forward/backward movement
void ACoFCharacter::MoveForwardBackward(float Value)
{
	if (Controller != nullptr && Value != 0.f) // Make sure we have input and a controller
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f); // Only get Yaw rotation
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X)); // Forward vector
		AddMovementInput(Direction, Value); // Move in that direction
	}
}

// Handles left/right movement
void ACoFCharacter::MoveRightLeft(float Value)
{
	if (Controller != nullptr && Value != 0.f) // Make sure we have input and a controller
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f); // Only get Yaw rotation
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y)); // Right vector
		AddMovementInput(Direction, Value); // Move in that direction
	}
}

// Handles left/right turning (camera yaw)
void ACoFCharacter::TurnRightLeft(float Value)
{
	AddControllerYawInput(Value); // Rotate character left/right based on input
}

// Handles up/down looking (camera pitch)
void ACoFCharacter::LookUpDown(float Value)
{
	AddControllerPitchInput(Value); // Rotate camera up/down based on input
}

// Called every frame
void ACoFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); // Call the base class Tick
}
