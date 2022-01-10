// Fill out your copyright notice in the Description page of Project Settings.


#include "Ennemies.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "BoidsGameInstance.h"

// Sets default values
AEnnemies::AEnnemies()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    VisualMesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

    if (CubeVisualAsset.Succeeded()){
        VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
        VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	// Create target
	target = CreateDefaultSubobject<UTargetComponent>(TEXT("Target"));
	target->SetupAttachment(RootComponent);

	// Create Nest
	nest = CreateDefaultSubobject<UNestComponent>(TEXT("Nest"));
	nest->SetupAttachment(RootComponent);

	this->Tags.Add(FName(TEXT("target")));
	this->Tags.Add(FName(TEXT("foe")));
}

// Called when the game starts or when spawned
void AEnnemies::BeginPlay()
{
	Super::BeginPlay();
	
	target->AttachParent(this);
	target->SetTargetTransform(this->GetTransform());
	nest->setParams(this->GetGameInstance<UBoidsGameInstance>()->getParameters(1));
	isAlive = true;
}

// Called every frame
void AEnnemies::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isAlive){
		Move(DeltaTime);
	}
	
}

void AEnnemies::Move(float DeltaTime){
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatSpeed;
	NewRotation.Yaw += DeltaTime * RotationSpeed;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

void AEnnemies::StartNMI(){
	isAlive = true;
}

bool AEnnemies::ReceiveDamage(float damageValue){
	health -= damageValue;
	if(health <= 0){
		this->HideActor();
		return true; //Is dead
	}
	//Flash to signal hit

	return false; //Is not dead
}

void AEnnemies::ShowActor(){
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void AEnnemies::HideActor(){
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}