// Fill out your copyright notice in the Description page of Project Settings.


#include "CoFAnimInstance.h"
#include "CoFCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCoFAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CoFCharacter = Cast<ACoFCharacter>(TryGetPawnOwner());
}

void UCoFAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (CoFCharacter == nullptr)
	{
		CoFCharacter = Cast<ACoFCharacter>(TryGetPawnOwner());
	}
	if (CoFCharacter == nullptr) return;

	FVector Velocity = CoFCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = CoFCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = CoFCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
}
