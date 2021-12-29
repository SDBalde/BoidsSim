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
	setCurrParams(UIManager->SetParameters(birdParams));
}
void UBoidsGameInstance::setCurrParams(ABirdParameters* newParams){
	currParams = newParams;
	UIManager->setCurrPlayerParam(currParams->getName());
}

void UBoidsGameInstance::LinkParameters(ABirdParameters* params){
	UE_LOG(LogTemp, Warning, TEXT("Link"));
	birdParams.Add(params);
}

ABirdParameters* UBoidsGameInstance::getParameters(int newParamIndex){
	FString newParamName = "";
	switch (newParamIndex)
	{
	case 1:
		newParamName = "General";
		break;
	case 2:
		newParamName = "Focused";
		break;
	case 3:
		newParamName = "Loose";
		break;
	default:
		break;
	}
	for(ABirdParameters* param:birdParams){
		if(param->getName() == newParamName){
			return param;
		}
	}
	return nullptr;
}
