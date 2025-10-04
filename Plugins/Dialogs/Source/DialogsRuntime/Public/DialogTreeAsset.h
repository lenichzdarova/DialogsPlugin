// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogRuntimeGraph.h"
#include "DialogTreeAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DIALOGSRUNTIME_API UDialogTreeAsset : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	FString Title = TEXT("Enter graph name here");
	UPROPERTY()
	UDialogRuntimeGraph* Graph = nullptr;
};
