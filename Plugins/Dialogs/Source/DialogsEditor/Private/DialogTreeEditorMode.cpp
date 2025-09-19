#include "DialogTreeEditorMode.h"
#include "DialogTreeDefaultTabFactory.h"

DialogTreeEditorMode::DialogTreeEditorMode(TSharedPtr<DialogTreeEditorApp> InApp) :
	FApplicationMode(TEXT("DialogTreeEditorMode"))
{
	App = InApp;	
	Tabs.RegisterFactory(MakeShareable(new DialogTreeDefaultTabFactory(InApp)));
	TabLayout = FTabManager::NewLayout("DialogTreeEditorMode_Layout_V1");

	auto Area = FTabManager::NewPrimaryArea();
	Area->SetOrientation(Orient_Vertical);	
	auto NewStack = FTabManager::NewStack();
	NewStack->AddTab(FName(TEXT("DialogTreeDefaultTab")), ETabState::OpenedTab);
	Area->Split(NewStack);
	TabLayout->AddArea(Area);	
}

void DialogTreeEditorMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<DialogTreeEditorApp> DialogAssetEditor = App.Pin();
	DialogAssetEditor->PushTabFactories(Tabs);
	FApplicationMode::RegisterTabFactories(InTabManager);
}

void DialogTreeEditorMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void DialogTreeEditorMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}
