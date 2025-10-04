// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogNodeInfo.h"
#include "DialogNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGSEDITOR_API UDialogNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override {return FLinearColor(FColor::Green);}
	virtual bool CanUserDeleteNode() const override {return true;}
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	UEdGraphPin* CreateDialogNodePin(EEdGraphPinDirection Direction, FName Name);

	
	void SetDialogNodeInfo(UDialogNodeInfo* InNodeInfo) { DialogNodeInfo = InNodeInfo; }
	UDialogNodeInfo* GetDialogNodeInfo() const { return DialogNodeInfo; }

private:
	UPROPERTY()
	UDialogNodeInfo* DialogNodeInfo = nullptr;
};
