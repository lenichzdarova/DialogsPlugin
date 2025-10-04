#include "DialogTreeDetailsTabFactory.h"
#include "DialogTreeEditorApp.h"
#include "DialogTreeAsset.h"
#include "PropertyEditorModule.h"

DialogTreeDetailsTabFactory::DialogTreeDetailsTabFactory(TSharedPtr<DialogTreeEditorApp> InApp) :
	FWorkflowTabFactory(FName("DialogTreeDetailsTab"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString(TEXT("Details"));
	ViewMenuDescription = FText::FromString(TEXT("Details"));
	ViewMenuTooltip = FText::FromString(TEXT("Tooltip"));
}

TSharedRef<SWidget> DialogTreeDetailsTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
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

	TSharedPtr<IDetailsView> SelectedNodeDetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	SelectedNodeDetailsView->SetObject(nullptr);
	EditorApp->SetSelectedNodeDetailView(SelectedNodeDetailsView);

	auto Widget = SNew(SVerticalBox);
	auto SlotDetailsView = Widget->AddSlot();
	SlotDetailsView.FillHeight(1.0f);
	SlotDetailsView.HAlign(HAlign_Fill);
	SlotDetailsView.AttachWidget(DetailsView.ToSharedRef());

	auto SlotSelectedNodeDetailsView = Widget->AddSlot();
	SlotSelectedNodeDetailsView.FillHeight(1.0f);
	SlotSelectedNodeDetailsView.HAlign(HAlign_Fill);
	SlotSelectedNodeDetailsView.AttachWidget(SelectedNodeDetailsView.ToSharedRef());
	return Widget;
}

FText DialogTreeDetailsTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("Details tab to edit dialog nods"));
}

