// Copyright 2023, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/SKGObjectDataTypes.h"
#include "Tick/SKGTickableObject.h"
#include "UObject/Object.h"
#include "SKGObject.generated.h"

class AActor;
class UWorld;

UCLASS(Blueprintable, BlueprintType)
class SKGUOBJECTS_API USKGObject : public USKGTickableObject
{
	GENERATED_BODY()
public:
	USKGObject();
	~USKGObject();

protected:
	UPROPERTY()
	mutable TObjectPtr<AActor> OwnerCache;
	AActor* FindOwner() const;

	UPROPERTY()
	mutable TObjectPtr<UWorld> WorldCache;
	UWorld* FindWorld() const;
	
	bool bIsBeingDestroyed = false;

	// Default Events ---------------------------------------------------------------
	// Ensure Super is called in order for BeginPlay to fire
	virtual void PostInitProperties() override;
	UFUNCTION(BlueprintImplementableEvent, Category = "SKGObject", meta = (DisplayName = "OnDestroyed"))
	void ReceiveOnDestroyed();
	// Calls RemoveReplicatedSubObject on the owner for this object, ensure parent function is called
	virtual void OnDestroyed();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "SKGObject", meta = (DisplayName = "BeginPlay"))
	void ReceiveBeginPlay();
	virtual void BeginPlay();
	// END OF Default Events ---------------------------------------------------------------

	// Ticking ---------------------------------------------------------------
	UPROPERTY(EditDefaultsOnly, Category = Tick)
	FSKGThumbnailData PrimaryObjectTick;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "SKGObject", meta = (DisplayName = "Tick"))
	void ReceiveTick();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SKGObject", meta = (DisplayName = "CanTick"))
	bool CanTick() const;
	virtual bool CanTick_Implementation() const { return true; }

	mutable double LastTickTime;
	virtual bool IsTickable() const override;
	// END OF Ticking ---------------------------------------------------------------
	
	virtual UWorld* GetGameWorldObject() const override;
	
public:
	UFUNCTION(BlueprintCallable, Category = "SKGObject")
	AActor* GetOwner() const { return OwnerCache ? OwnerCache : FindOwner(); }
	template<class T>
	T* GetOwner() const { return Cast<T>(GetOwner()); }
	UFUNCTION(BlueprintCallable, Category = "SKGObject")
	void SetOwner(AActor* NewOwner) const { OwnerCache = NewOwner; }
	
	virtual UWorld* GetWorld() const override { return WorldCache ? WorldCache : FindWorld(); }

	// Will start the process of destroying and call OnDestroyed. Make sure to null any references to object
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "SKGObject")
	void DestroyObject();

	UFUNCTION(BlueprintCallable, Category = "SKGNetworking")
	bool HasAuthority() const;

	UFUNCTION(BlueprintCallable, Category = "SKGTick")
	void SetObjectTickEnabled(bool bEnabled);
};
