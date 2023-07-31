// Copyright 2023, Dakota Dawe, All rights reserved


#include "Tick/SKGTickableObject.h"
#include "Tick/SKGTickableWorldSubsystem.h"

#include "Engine/World.h"


void USKGTickableObject::AddAsTickableObject()
{
	if (GetGameWorldObject())
	{
		if (USKGTickableWorldSubsystem* Subsystem = GetGameWorldObject()->GetSubsystem<USKGTickableWorldSubsystem>())
		{
			Subsystem->AddTickableObject(this);
		}
	}
}

void USKGTickableObject::RemoveTickableObject()
{
	if (GetGameWorldObject())
	{
		if (USKGTickableWorldSubsystem* Subsystem = GetGameWorldObject()->GetSubsystem<USKGTickableWorldSubsystem>())
		{
			Subsystem->RemoveTickableObject(this);
		}
	}
}
