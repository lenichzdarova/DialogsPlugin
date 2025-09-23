// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogTreeGraphSchema.h"
#include "DialogNode.h"

void UDialogTreeGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FDialogTreeNodeAction> NodeAction ( new FDialogTreeNodeAction(
		FText::FromString(TEXT("Nodes")),
		FText::FromString(TEXT("New node")),
		FText::FromString(TEXT("Create new node")),
		0));
	ContextMenuBuilder.AddAction(NodeAction);
}

UEdGraphNode* FDialogTreeNodeAction::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin,
	const FVector2D Location, bool bSelectNewNode)
{
	UDialogNode* Result = NewObject<UDialogNode>(ParentGraph);
	Result->NodePosX = Location.X;
	Result->NodePosY = Location.Y;
	Result->CreatePin(EEdGraphPinDirection::EGPD_Input, TEXT("Inputs"), TEXT("SomeInput"));
	Result->CreatePin(EEdGraphPinDirection::EGPD_Output, TEXT("Outputs"), TEXT("SomeOutput"));

	ParentGraph->Modify();
	ParentGraph->AddNode(Result, true, true);
	return Result;
}
