// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidsGameInstance.h"


UBoidsGameInstance::UBoidsGameInstance(const FObjectInitializer & ObjectInitializer){
    // Find the Widget and assigned to UIManagerClass
	static ConstructorHelpers::FClassFinder<UUserWidget> UIManagerBPClass(TEXT("/Game/BP/BirdParametersUI"));

	if (UIManagerBPClass.Class != nullptr)
	{
		UIManagerClass = UIManagerBPClass.Class;
	}
}

void UBoidsGameInstance::Init(){
	
}

void UBoidsGameInstance::OnLoadInGameMenu(){
    if (UIManagerClass == nullptr) return;

	UIManager = CreateWidget<UUIManager>(this, UIManagerClass);
	if (UIManager == nullptr) return;

	UIManager->AddToViewport();
	if(birdParams.Num() == 0) return;
	UIManager->SetParameters(birdParams);
	
	// Set the reference to the interface object
	//UIManager->SetMenuInterface(this);
}

void UBoidsGameInstance::LinkParameters(ABirdParameters* params){
	UE_LOG(LogTemp, Warning, TEXT("Link"));
	birdParams.Add(params);
	//if (UIManager == nullptr) return;
	//UIManager->ChangeTxt(FString::SanitizeFloat(birdParams->getTurnFactor()));
}
