// Copyright 2023, Dakota Dawe, All rights reserved


#include "Objects/SKGObject.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Tick/SKGTickableWorldSubsystem.h"

USKGObject::USKGObject()
{
	PrimaryObjectTick.bCanEverTick = false;
	PrimaryObjectTick.bStartWithTickEnabled = true;
}

USKGObject::~USKGObject()
{
	//DestroyObject();
}

AActor* USKGObject::FindOwner() const
{
	UObject* Owner = GetOuter();
	while (IsValid(Owner))
	{
		if (Owner->IsA(AActor::StaticClass()))
		{
			OwnerCache = Cast<AActor>(Owner);
			return OwnerCache;
		}
		Owner = Owner->GetOuter();
	}
	return nullptr;
}

UWorld* USKGObject::FindWorld() const
{
	if (GetOwner())
	{
		WorldCache = OwnerCache->GetWorld();
		return WorldCache;
	}

	return nullptr;
}

void USKGObject::DestroyObject()
{
	if (!bIsBeingDestroyed && GetOwner() && OwnerCache->HasAuthority())
	{
		bIsBeingDestroyed = true;
		OnDestroyed();
		ConditionalBeginDestroy();
	}
}

bool USKGObject::HasAuthority() const
{
	return GetOwner() ? OwnerCache->HasAuthority() : false;
}

void USKGObject::OnDestroyed()
{
	ReceiveOnDestroyed();
	if (GetOwner())
	{
		OwnerCache->RemoveReplicatedSubObject(this);
	}
}

void USKGObject::BeginPlay()
{
	ReceiveBeginPlay();
}

void USKGObject::Tick(float DeltaTime)
{
	ReceiveTick();
}

void USKGObject::SetObjectTickEnabled(bool bEnabled)
{
	if (PrimaryObjectTick.bCanEverTick)
	{
		PrimaryObjectTick.bTickStateEnabled = bEnabled;
	}
}

bool USKGObject::IsTickable() const
{
	if (PrimaryObjectTick.bTickStateEnabled)
	{
		if (GetWorld()->TimeSince(LastTickTime) > PrimaryObjectTick.TickInterval && CanTick())
		{
			LastTickTime = GetWorld()->GetTimeSeconds();
			return true;
		}
	}
	return false;
}

UWorld* USKGObject::GetGameWorldObject() const
{
	return GetWorld();
}

void USKGObject::PostInitProperties()
{
	UObject::PostInitProperties();
	if (GetWorld())
	{
		if (PrimaryObjectTick.bCanEverTick)
		{
			PrimaryObjectTick.bTickStateEnabled = PrimaryObjectTick.bStartWithTickEnabled;
			AddAsTickableObject();
		}
		BeginPlay();
	}
}
