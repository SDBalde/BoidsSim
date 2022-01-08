// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "BirdParameters.h"
#include "NestComponent.h"


// Sets default values
ABird::ABird()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BodyComp = CreateDefaultSubobject<USphereComponent>(TEXT("Body"));
	SM_Bird = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM Bird"));
	
	//BodyComp->SetupAttachment(RootComponent);
	//BodyComp->SetSimulatePhysics(false);
    //BodyComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Bird->SetWorldScale3D(FVector(0.1f,0.1f,0.1f));
	SM_Bird->SetSimulatePhysics(true);
	SM_Bird->SetEnableGravity(false);
	SM_Bird->SetLinearDamping(0.0f);
	SM_Bird->SetCollisionProfileName(TEXT("BirdCollisionPreset"));
	RootComponent = SM_Bird;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BirdAsset(TEXT("StaticMesh'/Game/Meshes/BirdMeshSphere.BirdMeshSphere'"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_BirdAsset(TEXT("StaticMesh'/Game/Meshes/BirdMeshCone.BirdMeshCone'"));
    SM_Bird->SetStaticMesh(SM_BirdAsset.Object);
	this->Tags.Add(FName(TEXT("bird")));
}

ABird::~ABird(){
	Unsubsrcibe();
}

void ABird::Subscribe(){
	if(settings != nullptr){
		settings->Subscribe(this);
	}
}

void ABird::Unsubsrcibe(){
	if(settings)settings->Unsubscribe(this);
}

void ABird::Update(void* msg){
	if(!settings)return;
	char* type = (char*)(msg);
	if(strcmp(type,"target") == 0){
		target = settings->getTarget();
	}else if(strcmp(type,"turnFactor") == 0){
		turnFactor = settings->getTurnFactor();
	}else if(strcmp(type,"visualRange") == 0){
		visualRange = settings->getVisualRange();
	}else if(strcmp(type,"protectedRange") == 0){
		protectedRange = settings->getProtectedRange();
	}else if(strcmp(type,"centeringFactor") == 0){
		centeringFactor = settings->getCenteringFactor();
	}else if(strcmp(type,"avoidFactor") == 0){
		avoidFactor = settings->getAvoidFactor();
	}else if(strcmp(type,"matchingFactor") == 0){
		matchingFactor = settings->getMatchingFactor();
	}else if(strcmp(type,"targetFactor") == 0){
		targetFactor = settings->getTargetFactor();
	}else if(strcmp(type,"maxSpeed") == 0){
		maxSpeed = settings->getMaxSpeed();
	}else if(strcmp(type,"minSpeed") == 0){
		minSpeed = settings->getMinSpeed();
	}else if(strcmp(type,"maxNeighbors") == 0){
		maxNeighbors = settings->getMaxNeighbors();
	}else if(strcmp(type,"debug") == 0){
		debug = settings->getDebug();
	}else if(strcmp(type,"parameters") == 0){
		auto newParam = settings->getParameters();
		 if(!newParam){
			 UE_LOG(LogTemp, Warning, TEXT("no new params"));
		 }if(!settings){
			 UE_LOG(LogTemp, Warning, TEXT("no settings"));
		 }

		if(newParam != settings && settings && newParam){
			Unsubsrcibe();
			this->settings = newParam;
			Subscribe();
		}
		
		UpdateParameters();
	}else{
		UpdateParameters();
	}
}

void ABird::UpdateParameters(){
	if(settings != nullptr){
		this->target = settings->getTarget();
		this->turnFactor = settings->getTurnFactor();
		this->visualRange = settings->getVisualRange();
		this->protectedRange = settings->getProtectedRange();
		this->centeringFactor = settings->getCenteringFactor();
		this->avoidFactor = settings->getAvoidFactor();
		this->matchingFactor = settings->getMatchingFactor();
		this->targetFactor = settings->getTargetFactor();
		this->maxSpeed = settings->getMaxSpeed();
		this->minSpeed = settings->getMinSpeed();
		this->maxNeighbors = settings->getMaxNeighbors();
		this->debug = settings->getDebug();
	}
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	if(settings){
		//settings = Cast<ABirdParameters>(Birdparameters);
		//if(!settings){
		//	UE_LOG(LogTemp, Warning, TEXT("no settings"));
		//}
		
		Subscribe();
		UpdateParameters();
	}
	if(target != nullptr){
		targetPosition = target->GetActorLocation();
	}
	vel = FVector(0,0,0);
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector posAvg = FVector(0,0,0);
	FVector velAvg = FVector(0,0,0);
	FVector close = FVector(0,0,0);
	FVector pos = GetActorLocation();
	int neighbors = 0;
	
	for (ABird *otherBird:birdList) //Check all bird range to find neighbors and too close
	{
		//ABird* otherBird = Cast<ABird>(other);
		if(otherBird == this){ // Skip if the other bird is this one
			continue;
		}
		FVector otherPos = otherBird->GetActorLocation();
		float dist = (pos - otherPos).Size();
		
		if(dist < visualRange){
			if(dist < protectedRange){
				close = close + (pos - otherPos);
				continue;
			}
			posAvg += otherPos;
			velAvg += otherBird->GetVel();
			neighbors++;
			if(neighbors >= this->maxNeighbors){
				break;
			}
		}
	}

	if(neighbors > 0){
		posAvg = posAvg / neighbors;
		velAvg = velAvg / neighbors;
		
		vel = (vel + (posAvg - pos)*centeringFactor + (velAvg - vel)*matchingFactor); // Match position and velocity of neighbors
		
	}

	vel = vel + (close * avoidFactor); // Avoid bird who are too close

	float RandX = FMath::RandRange(0,1)/1.0f;
	float RandY = FMath::RandRange(0,1)/1.0f;
	float RandZ = FMath::RandRange(0,1)/1.0f;
	vel = vel + FVector(RandX,RandY,RandZ) * randomMovement; // random movement

	if(target != nullptr){
		targetPosition = target->GetActorLocation();
		if((targetPosition - pos).Size() > 0)
			vel = vel + (targetPosition - pos)*targetFactor;
	}

	speed = vel.Size();
	if(speed > 0){ //Obtain direction of the movement
		dir = vel/speed;
	}else{
		dir = vel/minSpeed;
	}
	
	if(target != nullptr){
		float distToTarget = (targetPosition - pos).Size();
		if(distToTarget > 2*visualRange ){
			vel = dir * travelSpeed; // Travel faster when getting to target
		}else{
			ClampSpeed();	
		}
	}else{
		ClampSpeed();
	}

	//Check if bird will hit obstacle during forward movement
	FHitResult hitRes;
	FCollisionObjectQueryParams objParams(ECC_WorldStatic);
	bool hit = GetWorld()->LineTraceSingleByObjectType(hitRes,pos,pos+dir*protectedRange,objParams);
	if(hit){
		if(hitRes.GetActor()->ActorHasTag(FName(TEXT("foe"))) && hitRes.GetActor() == target){
			nest->DestroyBird(this);
		}else if(!hitRes.GetActor()->ActorHasTag(FName(TEXT("target"))) && !hitRes.GetActor()->ActorHasTag(FName(TEXT("bird")))){
			vel = -vel;
		}
		
		//try to move in opposite direction
		//TODO code ray scan to find unobstructed path
		//vel = vel + (dir-FVector(0,1,0))*turnfactor;
		//vel = vel + dir + (FVector(0,1,0)*turnFactor);
	}

	if(debug){ //Display debug info
		DrawDebugLine(GetWorld(), pos, (pos + dir*visualRange), FColor::Red); // The direction in which the bird is moving
		DrawDebugSphere(GetWorld(), pos, protectedRange, 8, FColor::Blue); // The protected range sphere
		DrawDebugSphere(GetWorld(), pos, visualRange, 8, FColor::Green); // The visual range sphere
		if(hit){
			DrawDebugBox(GetWorld(), hitRes.ImpactPoint, FVector(5,5,5), FColor::Green); // The incoming collision
		}
	}

	//set rotation to look at movement dir
	//SM_Bird->AddWorldRotation((dir.Rotation() - SM_Bird->GetUpVector().Rotation())*DeltaTime);
	//AddActorWorldRotation((dir.Rotation() - this->GetActorUpVector().Rotation()));

	this->SetActorLocation(pos + vel*DeltaTime);
}

void ABird::GetOtherBirds(){
	//birdList.Empty();
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABird::StaticClass(), birdList);
}

void ABird::SetBirdList(TArray<ABird*> newBirdList){
	this->birdList = newBirdList;
}

FVector ABird::GetVel(){
	return vel;
}

void ABird::ClampSpeed(){
	speed = vel.Size();
	if(speed < minSpeed){ // Clamp velocity between min and max speed
		vel = dir * minSpeed;
	}else if(speed > maxSpeed){
		vel = dir * maxSpeed;
	}
	speed = vel.Size();
}

void ABird::ShowBird(){
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void ABird::HideBird(){
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

void ABird::SetParameters(ABirdParameters* newParams){
	if(settings){
		Unsubsrcibe();
	}
	this->settings = newParams;
	Subscribe();
	UpdateParameters();
}

void ABird::SetNest(UNestComponent* newNest){
	this->nest = newNest;
}