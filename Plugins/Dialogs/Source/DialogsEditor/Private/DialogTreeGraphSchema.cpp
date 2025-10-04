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

const FPinConnectionResponse UDialogTreeGraphSchema::CanCreateConnection(const UEdGraphPin* A,
	const UEdGraphPin* B) const
{
	if (!A || !B)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, "Null pin");
	}

	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, "You can connect only inputs with outputs");
	}
	return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, "");
}

UEdGraphNode* FDialogTreeNodeAction::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin,
                                                   const FVector2D Location, bool bSelectNewNode)
{
	UDialogNode* Result = NewObject<UDialogNode>(ParentGraph);
	Result->CreateNewGuid();
	Result->NodePosX = Location.X;
	Result->NodePosY = Location.Y;
	Result->SetDialogNodeInfo(NewObject<UDialogNodeInfo>(Result));
	
	UEdGraphPin* InputPin = Result->CreateDialogNodePin(EGPD_Input, TEXT("Input"));
	Result->CreateDialogNodePin(EGPD_Output, TEXT("Output"));

	if (FromPin)
	{
		Result->GetSchema()->TryCreateConnection(FromPin, InputPin);
	}

	ParentGraph->Modify();
	ParentGraph->AddNode(Result, true, true);
	return Result;
}
