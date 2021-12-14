// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetComponent.h"

// Sets default values for this component's properties
UTargetComponent::UTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	targetStruct.targetName = FText::FromString(targetName);
}


// Called every frame
void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

FBirdTargetStruct UTargetComponent::getStruct(){
	return targetStruct;
}

void UTargetComponent::SetTargetTransform(const FTransform pos){
	targetStruct.targetPos = pos;
}
void UTargetComponent::AttachParent(AActor* parent){
	targetStruct.targetActor = parent;
}