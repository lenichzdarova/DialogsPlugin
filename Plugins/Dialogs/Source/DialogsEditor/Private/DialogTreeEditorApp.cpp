#include "DialogTreeEditorApp.h"
#include "DialogTreeEditorMode.h"
#include "DialogsRuntime/Public/DialogTree.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "DialogTreeGraphSchema.h"

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
	ActiveGrapth = FBlueprintEditorUtils::CreateNewGraph(ActiveDialogTree, NAME_None, UEdGraph::StaticClass(), UDialogTreeGraphSchema::StaticClass());
	InitAssetEditor(Mode, InToolkitHost, TEXT("DialogTreeEditorApp"), FTabManager::FLayout::NullLayout,
		true, true, ObjectToEdit);

	AddApplicationMode(TEXT("DialogTreeEditorMode"), MakeShareable(new DialogTreeEditorMode(SharedThis(this))));
	SetCurrentMode(TEXT("DialogTreeEditorMode"));
}
