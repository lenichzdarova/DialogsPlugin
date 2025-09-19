// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogsEditor.h"
#include "DialogTreeAssetAction.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "FDialogsModule"

void FDialogsEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTypeCategory =
		AssetToolsModule.RegisterAdvancedAssetCategory(FName(FName("Dialogs")), FText::FromString("Dialogs"));
	InternalRegisterTypeAction<DialogTreeAssetAction>("Dialog Asset");	
}

void FDialogsEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	const FAssetToolsModule* AssetToolsModulePtr = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");
	if (AssetToolsModulePtr)
	{
		IAssetTools& AssetTools = AssetToolsModulePtr->Get();
		for (const auto& Action : Actions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogsEditorModule, DialogsEditor)