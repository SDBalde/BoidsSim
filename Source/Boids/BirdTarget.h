// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetComponent.h"
#include "BirdTarget.generated.h"

UCLASS()
class BOIDS_API ABirdTarget : public AActor
{
	GENERATED_BODY()

	/** Target Position */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target, meta = (AllowPrivateAccess = "true"))
	class UTargetComponent* target;
	
public:	
	// Sets default values for this actor's properties
	ABirdTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** Returns target subobject **/
	FORCEINLINE class UTargetComponent* GetTarget() const { return target; }

};
