// Copyright 2023, Dakota Dawe, All rights reserved


#include "Statics/SKGInventoryFunctionsLibrary.h"
#include "Objects/SKGReplicatedObject.h"

#if DO_ENSURE
	#define ENSURE_OUTER_USING_REGISTERED_SUBOBJECT_LIST(InExpression, Outer) \
		ensureAlwaysMsgf(InExpression, TEXT("Outer: %s is not using bReplicateUsingRegisteredSubObjectList. MAKE SURE bReplicateUsingRegisteredSubObjectList UNDER Replication IS ENABLED FOR THIS OUTER"), *Outer->GetName())
	#define ENSURE_OUTER_TYPE_ACTOR_OR_COMPONENT(Outer) \
		ensureAlwaysMsgf(IsValid(Outer) && (Outer->IsA(AActor::StaticClass()) || Outer->IsA(UActorComponent::StaticClass())), TEXT("Outer is INVALID or NOT a Actor/ActorComponent"))
#else
	#define ENSURE_OUTER_USING_REGISTERED_SUBOBJECT_LIST(InExpression, Outer) InExpression
	#define ENSURE_OUTER_TYPE_ACTOR_OR_COMPONENT(Outer) IsValid(Outer)
#endif

USKGReplicatedObject* USKGInventoryFunctionsLibrary::CreateReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass)
{
	if (IsValid(Outer) && SubObjectClass)
	{
		return NewObject<USKGReplicatedObject>(Outer, SubObjectClass);
	}
	return nullptr;
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
	if (ENSURE_OUTER_TYPE_ACTOR_OR_COMPONENT(Outer) && IsValid(SubObject))
	{
		if (AActor* Actor = Cast<AActor>(Outer))
		{
			if (ENSURE_OUTER_USING_REGISTERED_SUBOBJECT_LIST(Actor->IsUsingRegisteredSubObjectList(), Actor))
			{
				Actor->AddReplicatedSubObject(SubObject, NetCondition);
				SubObject->SetOwner(Actor);
			}
		}
		else if (UActorComponent* ActorComponent = Cast<UActorComponent>(Outer))
		{
			if (ENSURE_OUTER_USING_REGISTERED_SUBOBJECT_LIST(ActorComponent->IsUsingRegisteredSubObjectList(), ActorComponent))
			{
				ActorComponent->AddReplicatedSubObject(SubObject, NetCondition);
				SubObject->SetOwner(ActorComponent->GetOwner());
			}
		}
	}
}

void USKGInventoryFunctionsLibrary::RemoveReplicatedSubObject(UObject* Outer, USKGReplicatedObject* SubObject)
{
	if (ENSURE_OUTER_TYPE_ACTOR_OR_COMPONENT(Outer) && IsValid(SubObject))
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