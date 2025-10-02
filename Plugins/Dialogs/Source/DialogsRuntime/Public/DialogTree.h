// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogRuntimePin.h"
#include "DialogTree.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DIALOGSRUNTIME_API UDialogTree : public UObject
{
	GENERATED_BODY()
	
public:	
	UPROPERTY()
	UDialogRuntimeGraph* Graph = nullptr;
};
