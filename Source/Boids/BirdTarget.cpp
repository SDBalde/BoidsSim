// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdTarget.h"

// Sets default values
ABirdTarget::ABirdTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create target
	target = CreateDefaultSubobject<UTargetComponent>(TEXT("Target"));
	target->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABirdTarget::BeginPlay()
{
	Super::BeginPlay();
	target->AttachParent(this);
	target->SetTargetTransform(this->GetTransform());
}

// Called every frame
void ABirdTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
