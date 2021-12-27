// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bird.h"
#include "Nest.generated.h"

UCLASS()
class BOIDS_API ANest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANest();

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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void InstantiateBirds();
	void SpawnBird();
	void DestroyBird();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void setNestSize(int newSize);

};
