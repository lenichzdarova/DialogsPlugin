#include "DialogTreeDefaultTabFactory.h"
#include "DialogTreeEditorApp.h"
#include "DialogTree.h"
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

	auto Widget = SNew(SVerticalBox);
	auto Slot = Widget->AddSlot();
	Slot.FillHeight(1.0f);
	Slot.HAlign(HAlign_Fill);
	//Slot.AttachWidget(SNew(STextBlock).Text(EditorApp->ActiveAsset()->GetName()));
	return Widget;
}

FText DialogTreeDefaultTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A primary view for doing primary things"));
}
