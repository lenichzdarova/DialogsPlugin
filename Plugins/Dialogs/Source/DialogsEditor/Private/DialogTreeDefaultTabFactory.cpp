#include "DialogTreeDefaultTabFactory.h"
#include "DialogTreeEditorApp.h"
#include "GraphEditor.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "PropertyEditorModule.h"

DialogTreeDefaultTabFactory::DialogTreeDefaultTabFactory(TSharedPtr<DialogTreeEditorApp> InApp) :
	FWorkflowTabFactory(FName("DialogTreeGraphTab"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString(TEXT("DialogGraph"));
	ViewMenuDescription = FText::FromString(TEXT("Default graph"));
	ViewMenuTooltip = FText::FromString(TEXT("Tooltip"));
}

TSharedRef<SWidget> DialogTreeDefaultTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<DialogTreeEditorApp> EditorApp = App.Pin();

	SGraphEditor::FGraphEditorEvents GraphEvents;
	GraphEvents.OnSelectionChanged.BindRaw(EditorApp.Get(), &DialogTreeEditorApp::OnGrapthSelectionChanged);
	
	TSharedPtr<SGraphEditor> GraphEditor = SNew(SGraphEditor)
		.IsEditable(true)
		.GraphEvents(GraphEvents)
		.GraphToEdit(EditorApp->GetActiveGraph());
	EditorApp->SetActiveGraphUI(GraphEditor);

	auto Widget = SNew(SVerticalBox);
	auto Slot = Widget->AddSlot();
	Slot.FillHeight(1.0f);
	Slot.HAlign(HAlign_Fill);		
	Slot.AttachWidget(GraphEditor.ToSharedRef());
	return Widget;
}

FText DialogTreeDefaultTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A primary view for doing primary things"));
}
