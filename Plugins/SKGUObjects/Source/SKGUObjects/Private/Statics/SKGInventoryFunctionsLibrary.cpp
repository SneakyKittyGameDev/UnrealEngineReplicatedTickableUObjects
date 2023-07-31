// Copyright 2023, Dakota Dawe, All rights reserved


#include "Statics/SKGInventoryFunctionsLibrary.h"
#include "Objects/SKGReplicatedObject.h"

USKGReplicatedObject* USKGInventoryFunctionsLibrary::CreateReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass)
{
	USKGReplicatedObject* SubObject = nullptr;
	if (IsValid(Outer) && SubObjectClass)
	{
		SubObject = NewObject<USKGReplicatedObject>(Outer, SubObjectClass);
	}
	return SubObject;
}

USKGReplicatedObject* USKGInventoryFunctionsLibrary::CreateAndAddReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> Class, ELifetimeCondition NetCondition)
{
	USKGReplicatedObject* SubObject = CreateReplicatedSubObject(Outer, Class);
	if (IsValid(SubObject))
	{
		AddReplicatedSubObject(Outer, SubObject, NetCondition);
	}
	return SubObject;
}

void USKGInventoryFunctionsLibrary::AddReplicatedSubObject(UObject* Outer, USKGReplicatedObject* SubObject, ELifetimeCondition NetCondition)
{
	if (IsValid(Outer) && IsValid(SubObject))
	{
		if (ensureAlwaysMsgf(IsActorOrActorComponent(Outer), TEXT("Outer is not a Actor or ActorComponent")))
		{
			if (AActor* Actor = Cast<AActor>(Outer))
			{
				if (ensureAlwaysMsgf(Actor->IsUsingRegisteredSubObjectList(), TEXT("Outer is not using bReplicateUsingRegisteredSubObjectList. MAKE SURE bReplicateUsingRegisteredSubObjectList UNDER Replication IS ENABLED FOR THIS OUTER")))
				{
					Actor->AddReplicatedSubObject(SubObject, NetCondition);
					SubObject->SetOwner(Actor);
				}
			}
			else if (UActorComponent* ActorComponent = Cast<UActorComponent>(Outer))
			{
				if (ensureAlwaysMsgf(ActorComponent->IsUsingRegisteredSubObjectList(), TEXT("Outer is not using bReplicateUsingRegisteredSubObjectList. MAKE SURE bReplicateUsingRegisteredSubObjectList UNDER Replication IS ENABLED FOR THIS OUTER")))
				{
					ActorComponent->AddReplicatedSubObject(SubObject, NetCondition);
					SubObject->SetOwner(ActorComponent->GetOwner());
				}
			}
		}
	}
}

void USKGInventoryFunctionsLibrary::RemoveReplicatedSubObject(UObject* Outer, USKGReplicatedObject* SubObject)
{
	if (IsValid(Outer) && IsValid(SubObject))
	{
		if (ensureMsgf(IsActorOrActorComponent(Outer), TEXT("Outer is not a Actor or ActorComponent")))
		{
			if (AActor* Actor = Cast<AActor>(Outer))
			{
				Actor->RemoveReplicatedSubObject(SubObject);
			}
			else if (UActorComponent* ActorComponent = Cast<UActorComponent>(Outer))
			{
				ActorComponent->RemoveReplicatedSubObject(SubObject);
			}
			SubObject->SetOwner(nullptr);
		}
	}
}