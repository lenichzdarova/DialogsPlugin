#include "DialogTreeDefaultTabFactory.h"
#include "DialogTreeEditorApp.h"
#include "DialogTree.h"
#include "PropertyEditorModule.h"

DialogTreeDefaultTabFactory::DialogTreeDefaultTabFactory(TSharedPtr<DialogTreeEditorApp> InApp) :
	FWorkflowTabFactory(FName("DialogGraph"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString(TEXT("DialogGraph"));
	ViewMenuDescription = FText::FromString(TEXT("Default graph"));
	ViewMenuTooltip = FText::FromString(TEXT("Tooltip"));
}

TSharedRef<SWidget> DialogTreeDefaultTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<DialogTreeEditorApp> EditorApp = App.Pin();
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bAllowSearch = false;
	DetailsViewArgs.bHideSelectionTip = true;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.bSearchInitialKeyFocus = true;
	DetailsViewArgs.bUpdatesFromSelection = false;
	DetailsViewArgs.NotifyHook = nullptr;
	DetailsViewArgs.bShowOptions = true;
	DetailsViewArgs.bShowModifiedPropertiesOption = false;
	DetailsViewArgs.bShowScrollBar = false;

	TSharedPtr<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(EditorApp->ActiveAsset());

	auto Widget = SNew(SVerticalBox);
	auto Slot = Widget->AddSlot();
	Slot.FillHeight(1.0f);
	Slot.HAlign(HAlign_Fill);
	Slot.AttachWidget(DetailsView.ToSharedRef());
	return Widget;
}

FText DialogTreeDefaultTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A primary view for doing primary things"));
}
