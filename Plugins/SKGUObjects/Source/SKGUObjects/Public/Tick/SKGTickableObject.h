// Copyright 2023, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SKGTickableObject.generated.h"

/**
 * 
 */
UCLASS()
class SKGUOBJECTS_API USKGTickableObject : public UObject
{
	GENERATED_BODY()
public:
	USKGTickableObject() {}
	virtual ~USKGTickableObject() {}
	
	virtual void Tick(float DeltaTime) {}
	virtual UWorld* GetGameWorldObject() const { return nullptr; }
	virtual bool IsTickable() const { return true; }

protected:
	void AddAsTickableObject();
	void RemoveTickableObject();
};
