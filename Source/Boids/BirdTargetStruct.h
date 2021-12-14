// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "BirdTargetStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct BOIDS_API FBirdTargetStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText targetName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* targetActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform targetPos;
	
	FBirdTargetStruct(){
		targetName = FText::FromString("NAME");
		targetActor = nullptr;
	}

	FTransform getTargetPos(){
		return targetPos;
	}
};
