// Copyright 2023, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Objects/SKGObject.h"
#include "Subsystems/WorldSubsystem.h"
#include "SKGTickableWorldSubsystem.generated.h"

class USKGTickableObject;

UCLASS()
class SKGUOBJECTS_API USKGTickableWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	friend USKGTickableObject;
public:
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(USKGTickableWorldSubsystem, STATGROUP_Tickables); }
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return TickableObjects.Num() > 0; }
	
protected:
	void AddTickableObject(USKGTickableObject* Object);
	void RemoveTickableObject(USKGTickableObject* Object);
	
	TArray<TObjectPtr<USKGTickableObject>> TickableObjects;
};
