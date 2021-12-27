// Fill out your copyright notice in the Description page of Project Settings.


#include "NestComponent.h"

// Sets default values for this component's properties
UNestComponent::UNestComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UNestComponent::BeginPlay()
{
	Super::BeginPlay();
	InstantiateBirds();
	timer = respawnRate;
	
}


// Called every frame
void UNestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(birdsAlive < nestSize){
		timer += DeltaTime;
		if(timer >= respawnRate){
			SpawnBird();
			timer = 0.0f;
		}
	}
}

void UNestComponent::setNestSize(int newSize){
	nestSize = newSize;
}

void UNestComponent::InstantiateBirds(){
	FVector spawnPos = GetComponentLocation();
	FRotator spawnRot = GetComponentRotation();
	ABird* birdSpawned;
	for(int i=0; i<nestSize; i++){
		birdSpawned = GetWorld()->SpawnActor<ABird>(spawnPos, spawnRot);
		birdSpawned->HideBird();
		birdSpawned->SetParameters(params);
		birdsListHidden.Add(birdSpawned);
	}
	
}

void UNestComponent::SpawnBird(){
	ABird* bird = birdsListHidden.Pop(false);
	bird->SetActorLocationAndRotation(GetComponentLocation(), GetComponentRotation());
	bird->ShowBird();
	birdsListShown.Add(bird);
	birdsAlive++;
}

void UNestComponent::DestroyBird(){
	ABird* bird = birdsListShown.Pop(false);
	bird->HideBird();
	birdsListHidden.Add(bird);
	birdsAlive--;
}

