// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdParameters.h"
#include "BoidsGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABirdParameters::ABirdParameters()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ABirdParameters::BeginPlay(){
	GetWorld()->GetGameInstance<UBoidsGameInstance>()->LinkParameters(this);
	targetStruct.targetActor = this;
	targetStruct.targetName = FText::FromString(this->paramName);
}

void ABirdParameters::changeParamValue(FString name, float newValue){
	if(name == "turnFactor"){
		setTurnFactor(newValue);
	}else if(name == "visualRange"){
		setVisualRange(newValue);
	}else if(name == "protectedRange"){
		setProtectedRange(newValue);
	}else if(name == "centeringFactor"){
		setCenteringFactor(newValue);
	}else if(name == "avoidFactor"){
		setAvoidFactor(newValue);
	}else if(name == "matchingFactor"){
		setMatchingFactor(newValue);
	}else if(name == "targetFactor"){
		setTargetFactor(newValue);
	}else if(name == "maxSpeed"){
		setMaxSpeed(newValue);
	}else if(name == "minSpeed"){
		setMinSpeed(newValue);
	}else if(name == "maxNeighbors"){
		setMaxNeighbors(newValue);
	}
}

AActor* ABirdParameters::getTarget(){
	return this->target;
}
ABirdParameters* ABirdParameters::getParameters(){
	return this->newParam;
}
float ABirdParameters::getTurnFactor(){
	return this->turnFactor;
}
float ABirdParameters::getVisualRange(){
	return this->visualRange;
}
float ABirdParameters::getProtectedRange(){
	return this->protectedRange;
}
float ABirdParameters::getCenteringFactor(){
	return this->centeringFactor;
}
float ABirdParameters::getAvoidFactor(){
	return this->avoidFactor;
}
float ABirdParameters::getMatchingFactor(){
	return this->matchingFactor;
}
float ABirdParameters::getTargetFactor(){
	return this->targetFactor;
}
float ABirdParameters::getMaxSpeed(){
	return this->maxSpeed;
}
float ABirdParameters::getMinSpeed(){
	return this->minSpeed;
}
int ABirdParameters::getMaxNeighbors(){
	return this->maxNeighbors;
}
bool ABirdParameters::getDebug(){
	return this->debug;
}
FBirdTargetStruct ABirdParameters::getStruct(){
	return targetStruct;
}
int ABirdParameters::getBirdCount(){
	return this->getSubscribersCount();
}

void ABirdParameters::setTarget(AActor* val){
	this->target = val;
	Notify("target");
}
void ABirdParameters::setParam(ABirdParameters* param){
	this->newParam = param;
	Notify("parameters");
}
void ABirdParameters::setTurnFactor(float val){
	this->turnFactor = val;
	Notify("turnFactor");
}
void ABirdParameters::setVisualRange(float val){
	this->visualRange = val;
	Notify("visualRange");
}
void ABirdParameters::setProtectedRange(float val){
	this->protectedRange = val;
	Notify("protectedRange");
}
void ABirdParameters::setCenteringFactor(float val){
	this->centeringFactor = val;
	Notify("centeringFactor");
}
void ABirdParameters::setAvoidFactor(float val){
	this->avoidFactor = val;
	Notify("avoidFactor");
}
void ABirdParameters::setMatchingFactor(float val){
	this->matchingFactor = val;
	Notify("matchingFactor");
}
void ABirdParameters::setTargetFactor(float val){
	this->targetFactor = val;
	Notify("targetFactor");
}
void ABirdParameters::setMaxSpeed(float val){
	this->maxSpeed = val;
	Notify("maxSpeed");
}
void ABirdParameters::setMinSpeed(float val){
	this->minSpeed = val;
	Notify("minSpeed");
}
void ABirdParameters::setMaxNeighbors(int val){
	this->maxNeighbors = val;
	Notify("maxNeighbors");
}
void ABirdParameters::setDebug(bool val){
	this->debug = val;
	Notify("debug");
} 