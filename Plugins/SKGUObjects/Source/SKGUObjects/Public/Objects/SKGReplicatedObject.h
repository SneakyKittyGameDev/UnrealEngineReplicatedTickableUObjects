// Copyright 2023, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "SKGObject.h"
#include "SKGReplicatedObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SKGUOBJECTS_API USKGReplicatedObject : public USKGObject
{
	GENERATED_BODY()
public:
	USKGReplicatedObject();
	~USKGReplicatedObject(); 

protected:
	// Replication -------------------------------------------------------------------------------------------------------
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;
	virtual bool CallRemoteFunction(UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack) override;
	// End of Replication ------------------------------------------------------------------------------------------------
};
