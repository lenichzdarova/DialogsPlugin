// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogsEditor.h"
#include "DialogTreeAssetAction.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "EdGraphUtilities.h"
#include "EdGraph/EdGraphPin.h"

#define LOCTEXT_NAMESPACE "FDialogsModule"

void FDialogsEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTypeCategory =
		AssetToolsModule.RegisterAdvancedAssetCategory(FName(FName("Dialogs")), FText::FromString("Dialogs"));
	InternalRegisterTypeAction<DialogTreeAssetAction>("Dialog Asset");

	// иконки
	StyleSet = MakeShareable(new FSlateStyleSet(TEXT("DialogTreeEditorStyle")));
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin("Dialogs");
	FString ContentDir = Plugin->GetBaseDir().Append(TEXT("/Resources"));
	StyleSet->SetContentRoot(ContentDir);
	
	FSlateImageBrush* ThumbnailBrush = new FSlateImageBrush(StyleSet->RootToContentDir
		(TEXT("DialogTreeAssetIcon"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush* AssetIconBrush = new FSlateImageBrush(StyleSet->RootToContentDir
		(TEXT("DialogTreeAssetIcon"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush* NodeAddPinIcon = new FSlateImageBrush(StyleSet->RootToContentDir
		(TEXT("NodeAddPinIcon"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush* NodeDeletePinIcon = new FSlateImageBrush(StyleSet->RootToContentDir
		(TEXT("NodeDeletePinIcon"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush* NodeDeleteNodeIcon = new FSlateImageBrush(StyleSet->RootToContentDir
		(TEXT("NodeDeleteNodeIcon"), TEXT(".png")), FVector2D(128, 128));

	StyleSet->Set("ClassThumbnail.DialogTree", ThumbnailBrush);
	StyleSet->Set("ClassIcon.DialogTree", AssetIconBrush);
	StyleSet->Set("DialogTreeEditor.NodeAddPinIcon", NodeAddPinIcon);
	StyleSet->Set("DialogTreeEditor.NodeDeletePinIcon", NodeDeletePinIcon);
	StyleSet->Set("DialogTreeEditor.NodeDeleteNodeIcon", NodeDeleteNodeIcon);
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);

	PinFactory = MakeShareable(new FDialogNodePinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(PinFactory);
}

void FDialogsEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.	
	
	if (const FAssetToolsModule* AssetToolsModulePtr = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools"))
	{
		IAssetTools& AssetTools = AssetToolsModulePtr->Get();
		for (const auto& Action : Actions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}
	Actions.Empty();

	FEdGraphUtilities::UnregisterVisualPinFactory(PinFactory);
	PinFactory.Reset();
	PinFactory = nullptr;
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
	StyleSet.Reset();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogsEditorModule, DialogsEditor)