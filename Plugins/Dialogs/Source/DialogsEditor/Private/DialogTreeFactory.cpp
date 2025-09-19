// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogTreeFactory.h"
#include "DialogTree.h"

UDialogTreeFactory::UDialogTreeFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UDialogTree::StaticClass();
}

UObject* UDialogTreeFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	UObject* ProxyObject = NewObject<UDialogTree>(InParent, SupportedClass, InName, Flags);
	return ProxyObject;
}




