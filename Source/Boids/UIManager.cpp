// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

void UUIManager::ChangeBirdParamValue(FString paramName, float newValue){
    UE_LOG(LogTemp, Warning, TEXT("%s newValue: %f"), *paramName, newValue);
	if(currParams){
		currParams->changeParamValue(paramName, newValue);
	}
}

ABirdParameters* UUIManager::SetParameters(TArray<ABirdParameters*> params){
	birdparameters = params;
	int birds = -1;
	for(ABirdParameters* param:params){
		if(birds < param->getBirdCount()){
			currParams = param;
			birds = param->getBirdCount();
		}
	}
	ChangeValues();
	selectParamTarget(currParams);
	return currParams;
}

void UUIManager::setTarget(AActor* target){
	currParams->setTarget(target);
}

void UUIManager::setParam(ABirdParameters* param){
	//currParams->setParam(param);
	currParams = param;
	ChangeValues();
}

void UUIManager::ChangeValues(){
	turnFactorTxt->SetText(FText::AsNumber(currParams->getTurnFactor()));
	visualRangeTxt->SetText(FText::AsNumber(currParams->getVisualRange()));
	protectedRangeTxt->SetText(FText::AsNumber(currParams->getProtectedRange()));
	centeringFactorTxt->SetText(FText::AsNumber(currParams->getCenteringFactor()));
	avoidFactorTxt->SetText(FText::AsNumber(currParams->getAvoidFactor()));
	matchingFactorTxt_1->SetText(FText::AsNumber(currParams->getMatchingFactor()));
	targetFactorTxt_1->SetText(FText::AsNumber(currParams->getTargetFactor()));
	maxSpeedTxt->SetText(FText::AsNumber(currParams->getMaxSpeed()));
	minSpeedTxt->SetText(FText::AsNumber(currParams->getMinSpeed()));
}

void UUIManager::setCurrPlayerParam(FString paramName){
	currPlayerParam->SetText(FText::FromString(paramName));
}

void UUIManager::setBirdAmountTxt(int numAlive, int nestSize){
	birdAmount->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), numAlive, nestSize)));
}