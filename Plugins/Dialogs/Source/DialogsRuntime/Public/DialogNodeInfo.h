// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogNodeInfo.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DIALOGSRUNTIME_API UDialogNodeInfo : public UObject
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere)
	FText Title;

	UPROPERTY(EditAnywhere)
	FText DialogText;

	UPROPERTY(EditAnywhere)
	TArray<FText> Responses;
};
