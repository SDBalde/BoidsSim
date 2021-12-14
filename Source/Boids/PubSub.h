// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class BOIDS_API Subscriber
{
public:
	virtual ~Subscriber(){};
	virtual void Update(void* msg);
};

class BOIDS_API Publisher
{
public:
	virtual ~Publisher(){};
	void Subscribe(Subscriber* sub){
		if(notifying){
			toSubList.Add(sub);
			return;
		}
		subList.Add(sub);
		subscribersCount++;
	};
	void Unsubscribe(Subscriber* sub){
		if(notifying){
			toUnsubList.Add(sub);
			return;
		}
		subList.Remove(sub);
		subscribersCount--;
	};
	void Notify(void* msg){
		UE_LOG(LogTemp, Warning, TEXT("Notifying"));
		notifying = true;
		for (Subscriber* sub:subList){
			sub->Update(msg);
		}
		notifying = false;
		Complete();
	}
	int getSubscribersCount(){return subscribersCount;};
private:
	TArray<Subscriber*> subList;
	TArray<Subscriber*> toSubList;
	TArray<Subscriber*> toUnsubList;
	bool notifying = false;
	int subscribersCount = 0;

	void Complete(){
		for(Subscriber* sub:toSubList){
			Subscribe(sub);
		}
		for(Subscriber* sub:toUnsubList){
			Unsubscribe(sub);
		}
		toSubList.Empty();
		toUnsubList.Empty();
	}
};