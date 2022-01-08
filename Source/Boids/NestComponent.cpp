// Fill out your copyright notice in the Description page of Project Settings.


#include "NestComponent.h"
#include "BoidsGameInstance.h"
#include "Kismet/GameplayStatics.h"

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
	initRespawnRate = spawnTime/nestSize;
	currRespawnRate = initRespawnRate;
	timer = initRespawnRate;
}

void UNestComponent::StartNest(){
	InstantiateBirds();
	isAwake = true;
}

// Called every frame
void UNestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(isAwake){
		if(birdsAlive < nestSize){
			timer += DeltaTime;
			if(timer >= currRespawnRate){
				SpawnBird();
				timer = 0.0f;
			}
		}else if(initSpawn){
			initSpawn = false;
			currRespawnRate = respawnRate;
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
		birdSpawned->SetNest(this);
		birdsListHidden.Add(birdSpawned);
		birdsList.Add(birdSpawned);
	}
	for(ABird* bird:birdsList){
		bird->SetBirdList(birdsList);
	}
}

void UNestComponent::SpawnBird(){
	if(birdsListHidden.Num()>0){
		ABird* bird = birdsListHidden.Pop(false);
		bird->SetActorLocationAndRotation(GetComponentLocation(), GetComponentRotation());
		bird->ShowBird();
		birdsListShown.Add(bird);
		birdsAlive++;
		NotifyBirdAmountChange();
	}
}

void UNestComponent::DestroyBird(ABird* bird){
	if(birdsListShown.Num()){
		bird->HideBird();
		birdsListShown.Remove(bird);
		birdsListHidden.Add(bird);
		birdsAlive--;
		NotifyBirdAmountChange();
	}
}

void UNestComponent::NotifyBirdAmountChange(){
	Cast<UBoidsGameInstance>(UGameplayStatics::GetGameInstance(this->GetWorld()))->setBirdAmountTxt(birdsAlive, nestSize);
}

void UNestComponent::setTarget(AActor* target){
	params->setTarget(target);
}

void UNestComponent::setNewParams(ABirdParameters* newParams){
	params->setParam(newParams);
	params = newParams;
}

void UNestComponent::setParams(ABirdParameters* newParams){
	this->params = newParams;
}


