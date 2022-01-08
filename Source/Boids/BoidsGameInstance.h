// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UIManager.h"
#include "BirdParameters.h"
#include "BoidsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BOIDS_API UBoidsGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	// Dynamic reference to the blueprint class
	TSubclassOf<class UUserWidget> UIManagerClass;

	// Internal reference to the blueprint for gameplay logic
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UUIManager* UIManager;
	TArray<ABirdParameters*> birdParams;
	ABirdParameters* currParams = nullptr;

public:	

	UBoidsGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init();
	
	FORCEINLINE class UUIManager* GetUIManager() const { return UIManager; }
	
public:

	// Interface IInGameMenuInterface
	// Method callable from blueprite to create the UI and add it to the viewport
	UFUNCTION(BlueprintCallable)
	void OnLoadInGameMenu();
	void LinkParameters(ABirdParameters* params);
	ABirdParameters* getParameters(int newParamIndex);
	void setCurrParams(ABirdParameters* newParams);
	void setBirdAmountTxt(int numAlive, int nestSize);
};
