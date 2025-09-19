// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogTreeFactory.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGSEDITOR_API UDialogTreeFactory : public UFactory
{
	GENERATED_BODY()

public:
	UDialogTreeFactory(const FObjectInitializer& ObjectInitializer);

public:	
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
