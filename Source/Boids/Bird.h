// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PubSub.h"
#include "Bird.generated.h"


UCLASS()
class BOIDS_API ABird : public AActor, public Subscriber
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABird();
	~ABird();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
    	//class USphereComponent* BodyComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Bird;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	class AActor* Birdparameters = nullptr; // The parameters that control the bird used to set in editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AActor* target = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float speed = 0; // The speed of bird
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector vel; // The velocity of the bird
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector dir; // The direction of the bird (direction)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<ABird*> birdList; // All the birds who are alive
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool debug = false; // Wether to activate the debug feature
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABirdParameters* settings = nullptr; // The parameters for control, used in code
	FVector targetPosition;
	class UNestComponent* nest = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
		float turnFactor = 100.0; // how hard to turn to avoid obstacles  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
		float visualRange = 75.0; // how far to see neighbors
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
		float protectedRange = 30.0; // how far to see birds who are too close
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
		float centeringFactor = 0.5;	// how hard to go towards the center of neighbors
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
		float avoidFactor = 5.0; // how hard to move away from birds who are too close
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
		float matchingFactor = 0.1; // how hard to match direction of neighbors
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
		float targetFactor = 0.1; // how hard to go to target
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
		float maxSpeed = 300.0; // Maximum movement speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
		float travelSpeed = 1000.0; // Maximum movement speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
		float minSpeed = 70.0; // minimum movement speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
		int maxNeighbors = 25; // maximum amount of birds who can be followed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
		float randomMovement = 1.0; // how random to move  

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attack")
		float damageValue = 1.0f;

	void GetOtherBirds();
	void UpdateParameters();
	void Subscribe(); // Subscribe to the parameters
	void Unsubsrcibe(); // Unsub to parameters
	void ClampSpeed();
	bool complete = true;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector GetVel();
	void Update(void* msg);
	void ShowBird();
	void HideBird();
	void SetParameters(ABirdParameters* newParams);
	void SetNest(UNestComponent* nest);
	void SetBirdList(TArray<ABird*> birdList);
};
