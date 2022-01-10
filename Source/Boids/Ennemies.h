// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetComponent.h"
#include "NestComponent.h"
#include "Ennemies.generated.h"

UCLASS()
class BOIDS_API AEnnemies : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnnemies();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool isAlive = false;

	UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* VisualMesh;

	/** Target Position */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target, meta = (AllowPrivateAccess = "true"))
	class UTargetComponent* target;

	/** Nest Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Nest, meta = (AllowPrivateAccess = "true"))
	class UNestComponent* nest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FloatingActor")
    float FloatSpeed = 60.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FloatingActor")
    float RotationSpeed = 150.0f;

	void Move(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartNMI();
	bool ReceiveDamage(float damageValue);
	void ShowActor();
	void HideActor();
};
