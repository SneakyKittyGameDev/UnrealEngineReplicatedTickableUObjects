// Copyright 2023, Dakota Dawe, All rights reserved

#pragma once

#include "SKGObjectDataTypes.generated.h"

USTRUCT()
struct FSKGThumbnailData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category = "SKGTick")
	uint8 bCanEverTick:1;
	UPROPERTY(EditAnywhere, Category = "SKGTick")
	uint8 bStartWithTickEnabled:1;
	/** The frequency in seconds at which this tick function will be executed.  If less than or equal to 0 then it will tick every frame */
	UPROPERTY(EditAnywhere, Category = "SKGTick", meta = (DisplayName = "Tick Interval (secs)"))
	float TickInterval {0.0f};

	uint8 bTickStateEnabled:1;
};