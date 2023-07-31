// Copyright 2023, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Objects/SKGReplicatedObject.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Objects/SKGReplicatedObject.h"
#include "SKGInventoryFunctionsLibrary.generated.h"


UCLASS()
class SKGUOBJECTS_API USKGInventoryFunctionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
protected:
	static bool IsActorOrActorComponent(UObject* Object) { return Object->IsA(AActor::StaticClass()) || Object->IsA(UActorComponent::StaticClass()); }
public:
	UFUNCTION(BlueprintCallable, Category = "SKGInventoryStatics | Object", meta = (DeterminesOutputType = "SubObjectClass"))
	static USKGReplicatedObject* CreateReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass);
	UFUNCTION(BlueprintCallable, Category = "SKGInventoryStatics | Object", meta = (DeterminesOutputType = "SubObjectClass"))
	static USKGReplicatedObject* CreateAndAddReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass, ELifetimeCondition NetCondition);

	template<class T>
	static T* CreateReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass);
	template<class T>
	static T* CreateAndAddReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass, ELifetimeCondition NetCondition);
	
	// Adds the object to the replicated subobjects list. Remember to ensure bReplicateUsingRegisteredSubObjectList is true on the Outer
	UFUNCTION(BlueprintCallable, Category = "SKGInventory | Network")
	static void AddReplicatedSubObject(UObject* Outer, USKGReplicatedObject* SubObject, ELifetimeCondition NetCondition);
	// Removes the object from the replicated subobjects list. Remember to ensure bReplicateUsingRegisteredSubObjectList is true on the Outer
	UFUNCTION(BlueprintCallable, Category = "SKGInventory | Network")
	static void RemoveReplicatedSubObject(UObject* Outer, USKGReplicatedObject* SubObject);
};

template <class T>
T* USKGInventoryFunctionsLibrary::CreateReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass)
{
	USKGReplicatedObject* SubObject = nullptr;
	if (SubObjectClass && Outer && SubObjectClass->IsChildOf<T>())
	{
		SubObject = NewObject<USKGReplicatedObject>(Outer, SubObjectClass);
	}
	return Cast<T>(SubObject);
}

template <class T>
T* USKGInventoryFunctionsLibrary::CreateAndAddReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass, ELifetimeCondition NetCondition)
{
	T* Object = CreateReplicatedSubObject<T>(Outer, SubObjectClass);
	if (Object)
	{
		AddReplicatedSubObject(Outer, Object, NetCondition);
	}
	return Object;
}
