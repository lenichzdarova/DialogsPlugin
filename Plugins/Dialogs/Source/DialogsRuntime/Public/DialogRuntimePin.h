// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogRuntimePin.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGSRUNTIME_API UDialogRuntimePin : public UObject
{
	GENERATED_BODY()

	public:
	UPROPERTY()
	FName PinName;

	UPROPERTY()
	FGuid PinID;

	UPROPERTY()
	UDialogRuntimePin* Connection = nullptr;
};

UCLASS()
class DIALOGSRUNTIME_API UDialogRuntimeNode : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UDialogRuntimePin* InputPin = nullptr;
	UPROPERTY()
	TArray<UDialogRuntimePin*> OutputPins;
	UPROPERTY()
	FVector2D Location;

	//непосредственно диалоговые данные ноды
	UPROPERTY()
	UObject* NodeData = nullptr;
};

UCLASS()
class DIALOGSRUNTIME_API UDialogRuntimeGraph : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	TArray<UDialogRuntimeNode*> Nodes;	
};
