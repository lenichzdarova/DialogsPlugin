#include "DialogTreeEditorApp.h"
#include "DialogTreeEditorMode.h"
#include "DialogsRuntime/Public/DialogTree.h"

void DialogTreeEditorApp::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

void DialogTreeEditorApp::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost> InToolkitHost,
	UObject* InUObject)
{
	TArray<UObject*> ObjectToEdit;
	ObjectToEdit.Add(InUObject);
	ActiveDialogTree = Cast<UDialogTree>(InUObject);
	InitAssetEditor(Mode, InToolkitHost, TEXT("DialogTreeEditorApp"), FTabManager::FLayout::NullLayout,
		true, true, ObjectToEdit);

	AddApplicationMode(TEXT("DialogTreeEditorMode"), MakeShareable(new DialogTreeEditorMode(SharedThis(this))));
	SetCurrentMode(TEXT("DialogTreeEditorMode"));
}
