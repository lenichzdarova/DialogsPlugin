// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "AssetTypeActions_Base.h"
#include "Styling/SlateStyle.h"

class FDialogsEditorModule : public IModuleInterface
{
	EAssetTypeCategories::Type AssetTypeCategory = EAssetTypeCategories::None;
public:
	TArray<TSharedRef<IAssetTypeActions>> Actions;
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


private:
	TSharedPtr<FSlateStyleSet> StyleSet = nullptr;

private:
	template <class T>
	void InternalRegisterTypeAction(const FString& Name)
	{
		IAssetTools& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		const auto Action = MakeShared<T>(AssetTypeCategory);
		Actions.Emplace(Action);
		AssetToolsModule.RegisterAssetTypeActions(Action);
	}
};
