// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Bird.h"
#include "BirdParameters.h"
#include "GameFramework/Actor.h"
#include "NestComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOIDS_API UNestComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNestComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int nestSize = 300; // The amount of birds belonging to this nest
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int birdsAlive = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<ABird*> birdsListHidden;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<ABird*> birdsListShown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABirdParameters* params;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float respawnRate = 0.1f;
	float timer = 0.0f;
	bool isAwake = false;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InstantiateBirds();
	void SpawnBird();
	void DestroyBird();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void setNestSize(int newSize);
	void setTarget(AActor* target);
	void setNewParams(ABirdParameters* newParams);
	void setParams(ABirdParameters* newParams);
	void StartNest();

};
