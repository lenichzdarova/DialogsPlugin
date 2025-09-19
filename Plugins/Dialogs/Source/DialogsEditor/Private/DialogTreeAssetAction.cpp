#include "DialogTreeAssetAction.h"
#include "DialogTree.h"
#include "DialogTreeEditorApp.h"

DialogTreeAssetAction::DialogTreeAssetAction(EAssetTypeCategories::Type InCategory)
{
	Category = InCategory;
}
FText DialogTreeAssetAction::GetName() const
{
	return FText::FromString(TEXT("DialogTree"));
}
FColor DialogTreeAssetAction::GetTypeColor() const
{
	return FColor::Red;
}
UClass* DialogTreeAssetAction::GetSupportedClass() const
{
	return UDialogTree::StaticClass();
}
void DialogTreeAssetAction::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()? EToolkitMode::WorldCentric: EToolkitMode::Standalone;
	for (UObject* Object : InObjects)
	{
		if (UDialogTree* DialogAsset = Cast<UDialogTree>(Object))
		{
			TSharedPtr<DialogTreeEditorApp> Editor(new DialogTreeEditorApp);
			Editor->InitEditor(Mode, EditWithinLevelEditor, DialogAsset);
		}
	}
}
uint32 DialogTreeAssetAction::GetCategories()
{
	return Category;
}