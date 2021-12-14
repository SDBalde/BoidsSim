// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PubSub.h"
#include "Blueprint/UserWidget.h"
#include "BirdTargetStruct.h"
#include "BirdParameters.generated.h"

UCLASS()
class BOIDS_API ABirdParameters : public AActor, public Publisher
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABirdParameters();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString paramName = "UNDEFINED";
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		struct FBirdTargetStruct targetStruct;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AActor* target = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float turnFactor = 100.0; // how hard to turn to avoid 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float visualRange = 75.0; // how far to see neighbors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float protectedRange = 30.0; // how far to see birds who are too close
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float centeringFactor = 0.5;	// how hard to go towards the center of neighbors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float avoidFactor = 1.0; // how hard to move away from birds who are too close
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float matchingFactor = 0.1; // how hard to match direction of neighbors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float targetFactor = 5.0; // how hard to go to target
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxSpeed = 300.0; // Maximum movement speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float minSpeed = 70.0; // minimum movement speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxNeighbors = 25; // maximum amount of birds who can be followed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool debug = false; // activate the debug feature
	ABirdParameters* newParam = nullptr;

public:	

	void changeParamValue(FString name, float newValue);

	AActor* getTarget();
	ABirdParameters* getParameters();
	float getTurnFactor();
	float getVisualRange();
	float getProtectedRange();
	float getCenteringFactor();
	float getAvoidFactor();
	float getMatchingFactor();
	float getTargetFactor();
	float getMaxSpeed();
	float getMinSpeed();
	int getMaxNeighbors();
	bool getDebug();
	UFUNCTION(BlueprintCallable)
		FBirdTargetStruct getStruct();
	UFUNCTION(BlueprintCallable)
		int getBirdCount(); // The amount of birds who follow

	void setTarget(AActor* val);
	void setParam(ABirdParameters* param);
	void setTurnFactor(float val);
	void setVisualRange(float val);
	void setProtectedRange(float val);
	void setCenteringFactor(float val);
	void setAvoidFactor(float val);
	void setMatchingFactor(float val);
	void setTargetFactor(float val);
	void setMaxSpeed(float val);
	void setMinSpeed(float val);
	void setMaxNeighbors(int val);
	void setDebug(bool val);

};
