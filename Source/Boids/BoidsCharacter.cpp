// Copyright Epic Games, Inc. All Rights Reserved.

#include "BoidsCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "TargetComponent.h"
#include "BoidsGameInstance.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"

//////////////////////////////////////////////////////////////////////////
// ABoidsCharacter

ABoidsCharacter::ABoidsCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->bCheatFlying = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create target
	target = CreateDefaultSubobject<UTargetComponent>(TEXT("Target"));
	target->SetupAttachment(RootComponent);

	// Create Nest
	nest = CreateDefaultSubobject<UNestComponent>(TEXT("Nest"));
	nest->SetupAttachment(RootComponent);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

// Called when the game starts or when spawned
void ABoidsCharacter::BeginPlay()
{
	Super::BeginPlay();
	target->AttachParent(this);
	target->SetTargetTransform(this->GetTransform());
}
//////////////////////////////////////////////////////////////////////////
// Input

void ABoidsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABoidsCharacter::ActivateFlying);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ABoidsCharacter::ShootTarget);
	PlayerInputComponent->BindAction("TargetActor", IE_Pressed, this, &ABoidsCharacter::TargetActor);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	DECLARE_DELEGATE_OneParam(FCustomInputDelegate, const int);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("Formation1", IE_Pressed, this, &ABoidsCharacter::ChangeFormation, 1);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("Formation2", IE_Pressed, this, &ABoidsCharacter::ChangeFormation, 2);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("Formation3", IE_Pressed, this, &ABoidsCharacter::ChangeFormation, 3);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABoidsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABoidsCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ABoidsCharacter::MoveUp);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABoidsCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABoidsCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABoidsCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABoidsCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABoidsCharacter::OnResetVR);
}


void ABoidsCharacter::OnResetVR()
{
	// If Boids is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in Boids.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABoidsCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ABoidsCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ABoidsCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABoidsCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABoidsCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABoidsCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ABoidsCharacter::MoveUp(float Value){
	
	if ( (Controller != nullptr) && (Value != 0.0f) && (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Flying))
	{
		// find out which way is up
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get up vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ABoidsCharacter::ActivateFlying(){
	if(GetCharacterMovement()->IsFalling()){
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	}else if(GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Flying){
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}else{
		Jump();
	}
}

void ABoidsCharacter::ChangeFormation(int newFormation){
	this->GetGameInstance<UBoidsGameInstance>()->ChangeParameters(newFormation);
}

void ABoidsCharacter::ShootTarget(){
	FHitResult hitRes;
	FCollisionObjectQueryParams objParams(ECC_WorldStatic);
	objParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	bool hit = GetWorld()->LineTraceSingleByObjectType(hitRes,CameraBoom->GetComponentLocation(),CameraBoom->GetComponentLocation()+FollowCamera->GetForwardVector()*10000.0f,objParams);
	if(hit){
		//DrawDebugLine(GetWorld(), CameraBoom->GetComponentLocation(), (CameraBoom->GetComponentLocation()+FollowCamera->GetForwardVector()*10000.0f), FColor::Red, false, 1.0f);
		//DrawDebugBox(GetWorld(), hitRes.ImpactPoint, FVector(5,5,5), FColor::Green, false, 1.0f); // The incoming collision
		if(hitRes.GetActor()->ActorHasTag(FName(TEXT("target")))){
			this->GetGameInstance<UBoidsGameInstance>()->ChangeTarget(hitRes.GetActor());
		}
	}
}

void ABoidsCharacter::TargetActor(){
	this->GetGameInstance<UBoidsGameInstance>()->ChangeTarget(this);
}
