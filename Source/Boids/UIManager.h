// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/ListView.h"
#include "BirdParameters.h"
#include "Actor.h"
#include "UIManager.generated.h"

/**
 * 
 */
UCLASS()
class BOIDS_API UUIManager : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ABirdParameters*> birdparameters; // The parameters that control the bird

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UListView* TargetList;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEditableTextBox* turnFactorTxt;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEditableTextBox* visualRangeTxt;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEditableTextBox* protectedRangeTxt;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEditableTextBox* centeringFactorTxt;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEditableTextBox* avoidFactorTxt;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEditableTextBox* matchingFactorTxt_1;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEditableTextBox* targetFactorTxt_1;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEditableTextBox* maxSpeedTxt;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
		class UEditableTextBox* minSpeedTxt;
	
	ABirdParameters* currParams = nullptr;

	void ChangeValues();

public:
	UFUNCTION(BlueprintCallable)
		void ChangeBirdParamValue(FString paramName, float newValue);
	UFUNCTION(BlueprintCallable)
		void setTarget(AActor* target);
	void SetParameters(TArray<ABirdParameters*> params);
	UFUNCTION(BlueprintCallable)
		void setParam(ABirdParameters* param);
	UFUNCTION(BlueprintImplementableEvent)
		void selectParamTarget(ABirdParameters* param);
};	
