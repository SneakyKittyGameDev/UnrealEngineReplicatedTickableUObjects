// Copyright 2023, Dakota Dawe, All rights reserved


#include "Tick/SKGTickableWorldSubsystem.h"
#include "Tick/SKGTickableObject.h"

void USKGTickableWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool bShrinkArray = false;
	for (int32 i = 0; i < TickableObjects.Num(); ++i)
	{
		if (USKGTickableObject* Object = TickableObjects[i].Get())
		{
			if (Object->IsTickable())
			{
				Object->Tick(DeltaTime);
			}
		}
		else
		{
			bShrinkArray = true;
			TickableObjects.RemoveAt(i, 1, false);
		}
	}

	if (bShrinkArray)
	{
		TickableObjects.Shrink();
	}
}

void USKGTickableWorldSubsystem::AddTickableObject(USKGTickableObject* Object)
{
	TickableObjects.Add(Object);
}

void USKGTickableWorldSubsystem::RemoveTickableObject(USKGTickableObject* Object)
{
	TickableObjects.Remove(Object);
	TickableObjects.Shrink();
}
