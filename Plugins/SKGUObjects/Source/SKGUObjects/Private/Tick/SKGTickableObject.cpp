// Copyright 2023, Dakota Dawe, All rights reserved


#include "Tick/SKGTickableObject.h"
#include "Tick/SKGTickableWorldSubsystem.h"

#include "Engine/World.h"


void USKGTickableObject::AddAsTickableObject()
{
	if (const UWorld* World = GetWorld())
	{
		if (USKGTickableWorldSubsystem* Subsystem = World->GetSubsystem<USKGTickableWorldSubsystem>())
		{
			Subsystem->AddTickableObject(this);
		}
	}
}

void USKGTickableObject::RemoveTickableObject()
{
	if (const UWorld* World = GetWorld())
	{
		if (USKGTickableWorldSubsystem* Subsystem = World->GetSubsystem<USKGTickableWorldSubsystem>())
		{
			Subsystem->RemoveTickableObject(this);
		}
	}
}