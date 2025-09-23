// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogNode.h"
#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"

void UDialogNode::GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialog node actions")));
	UDialogNode* Node = (UDialogNode*)this;
	Section.AddMenuEntry(
		TEXT("AddPinEntry"),
		FText::FromString(TEXT("Add pin")),
		FText::FromString(TEXT("Creates a new pin")),
		FSlateIcon(TEXT("DialogTreeEditorStyle"), TEXT("DialogTreeEditor.NodeAddPinIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[Node]()
			{
				Node->CreatePin(EEdGraphPinDirection::EGPD_Output, TEXT("Outputs"), TEXT("AnotherOutput"));
				Node->GetGraph()->NotifyGraphChanged();
				Node->GetGraph()->Modify();
			}
			)));

	Section.AddMenuEntry(
		TEXT("DeletePinEntry"),
		FText::FromString(TEXT("Delete pin")),
		FText::FromString(TEXT("Delete last pin")),
		FSlateIcon(TEXT("DialogTreeEditorStyle"), TEXT("DialogTreeEditor.NodeDeletePinIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[Node]()
			{
				UEdGraphPin* Pin = Node->GetPinAt(Node->Pins.Num() - 1);
				if (Pin->Direction != EEdGraphPinDirection::EGPD_Input)
				{
					Node->RemovePin(Pin);
					Node->GetGraph()->NotifyGraphChanged();
					Node->GetGraph()->Modify();
				}				
			}
			)));

	Section.AddMenuEntry(
		TEXT("DeleteNodeEntry"),
		FText::FromString(TEXT("Delete node")),
		FText::FromString(TEXT("Delete selected node")),
		FSlateIcon(TEXT("DialogTreeEditorStyle"), TEXT("DialogTreeEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[Node]()
			{
				Node->GetGraph()->RemoveNode(Node);				
			}
			)));
}
