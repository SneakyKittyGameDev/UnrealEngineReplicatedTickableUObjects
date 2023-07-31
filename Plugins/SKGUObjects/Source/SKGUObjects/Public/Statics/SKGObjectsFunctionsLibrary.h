// Copyright 2023, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Objects/SKGReplicatedObject.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Objects/SKGReplicatedObject.h"
#include "SKGObjectsFunctionsLibrary.generated.h"


UCLASS()
class SKGUOBJECTS_API USKGObjectsFunctionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SKGInventoryStatics | Object", meta = (DeterminesOutputType = "SubObjectClass"))
	static USKGReplicatedObject* CreateReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass);
	UFUNCTION(BlueprintCallable, Category = "SKGInventoryStatics | Object", meta = (DeterminesOutputType = "SubObjectClass"))
	static USKGReplicatedObject* CreateAndRegisterReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass, ELifetimeCondition NetCondition);

	template<class T>
	static T* CreateReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass);
	template<class T>
	static T* CreateAndRegisterReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass, ELifetimeCondition NetCondition);
	
	// Adds the object to the replicated subobjects list. Remember to ensure bReplicateUsingRegisteredSubObjectList is true on the Outer
	UFUNCTION(BlueprintCallable, Category = "SKGInventory | Network")
	static void RegisterReplicatedSubObject(UObject* Outer, USKGReplicatedObject* SubObject, ELifetimeCondition NetCondition);
	// Removes the object from the replicated subobjects list. Remember to ensure bReplicateUsingRegisteredSubObjectList is true on the Outer
	UFUNCTION(BlueprintCallable, Category = "SKGInventory | Network")
	static void UnRegisterReplicatedSubObject(UObject* Outer, USKGReplicatedObject* SubObject);
};

template <class T>
T* USKGObjectsFunctionsLibrary::CreateReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass)
{
	USKGReplicatedObject* SubObject = nullptr;
	if (SubObjectClass && Outer && SubObjectClass->IsChildOf<T>())
	{
		SubObject = NewObject<USKGReplicatedObject>(Outer, SubObjectClass);
	}
	return Cast<T>(SubObject);
}

template <class T>
T* USKGObjectsFunctionsLibrary::CreateAndRegisterReplicatedSubObject(UObject* Outer, TSubclassOf<USKGReplicatedObject> SubObjectClass, ELifetimeCondition NetCondition)
{
	T* Object = CreateReplicatedSubObject<T>(Outer, SubObjectClass);
	if (Object)
	{
		RegisterReplicatedSubObject(Outer, Object, NetCondition);
	}
	return Object;
}
