#include "DialogTreeEditorMode.h"
#include "DialogTreeDefaultTabFactory.h"
#include "DialogTreeDetailsTabFactory.h"

DialogTreeEditorMode::DialogTreeEditorMode(TSharedPtr<DialogTreeEditorApp> InApp) :
	FApplicationMode(TEXT("DialogTreeEditorMode"))
{
	App = InApp;	
	Tabs.RegisterFactory(MakeShareable(new DialogTreeDefaultTabFactory(InApp)));
	Tabs.RegisterFactory(MakeShareable(new DialogTreeDetailsTabFactory(InApp)));
	TabLayout = FTabManager::NewLayout("DialogTreeEditorMode_Layout_V1");

	auto Area = FTabManager::NewPrimaryArea();	
	Area->SetOrientation(Orient_Vertical);
	
	auto Splitter = FTabManager::NewSplitter();
	Splitter->SetOrientation(Orient_Horizontal);

	auto GrapthStack = FTabManager::NewStack();
	GrapthStack->SetSizeCoefficient(0.75f);
	GrapthStack->AddTab(FName(TEXT("DialogTreeGraphTab")), ETabState::OpenedTab);
	Splitter->Split(GrapthStack);
	
	auto DetailsStack = FTabManager::NewStack();
	DetailsStack->SetSizeCoefficient(0.25f);
	DetailsStack->AddTab(FName(TEXT("DialogTreeDetailsTab")), ETabState::OpenedTab);
	Splitter->Split(DetailsStack);
	
	Area->Split(Splitter);
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
