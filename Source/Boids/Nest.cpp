// Fill out your copyright notice in the Description page of Project Settings.


#include "Nest.h"

// Sets default values
ANest::ANest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANest::BeginPlay()
{
	Super::BeginPlay();
	InstantiateBirds();
	timer = respawnRate;
}

// Called every frame
void ANest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(birdsAlive < nestSize){
		timer += DeltaTime;
		if(timer >= respawnRate){
			SpawnBird();
			timer = 0.0f;
		}
	}
	
}

void ANest::setNestSize(int newSize){
	nestSize = newSize;
}

void ANest::InstantiateBirds(){
	FVector spawnPos = GetActorLocation();
	FRotator spawnRot = GetActorRotation();
	ABird* birdSpawned;
	for(int i=0; i<nestSize; i++){
		birdSpawned = GetWorld()->SpawnActor<ABird>(spawnPos, spawnRot);
		birdSpawned->HideBird();
		birdSpawned->SetParameters(params);
		birdsListHidden.Add(birdSpawned);
	}
	
}

void ANest::SpawnBird(){
	ABird* bird = birdsListHidden.Pop(false);
	bird->ShowBird();
	birdsListShown.Add(bird);
	birdsAlive++;
}

void ANest::DestroyBird(){
	ABird* bird = birdsListShown.Pop(false);
	bird->HideBird();
	birdsListHidden.Add(bird);
	birdsAlive--;
}