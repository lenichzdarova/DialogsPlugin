#pragma once
#include "CoreMinimal.h"
#include "DialogTreeAsset.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class DialogTreeEditorApp : public FWorkflowCentricApplication,
	public FEditorUndoClient, public FNotifyHook
{
public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost> InToolkitHost,
		UObject* InUObject);

	class UDialogTreeAsset* ActiveAsset() const {return OpenedAsset;}
	UEdGraph* GetActiveGraph() const {return Graph;}
	void SetActiveGraph(UEdGraph* InActiveGraph) {Graph = InActiveGraph;}

	void SetActiveGraphUI(TSharedPtr<SGraphEditor> InGraph) { ActiveGraphUI = InGraph; }
	void SetSelectedNodeDetailView(TSharedPtr<IDetailsView> InDetailsView);
	void OnGrapthSelectionChanged(const FGraphPanelSelectionSet& InSelection);

	
	
public: //FAssetEditorToolkitInterface
	virtual FName GetToolkitFName() const override {return FName(TEXT("DialogTreeEditorApp"));}
	virtual FText GetBaseToolkitName() const override {return FText::FromString(TEXT("DialogTreeEditorApp"));}
	virtual FString GetWorldCentricTabPrefix() const override {return TEXT("DialogTreeEditorApp");}
	virtual FLinearColor GetWorldCentricTabColorScale() const override
		{return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);}
	virtual FString GetDocumentationLink() const override {return FString("");}
	virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override {};
	virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override {};

	virtual void OnClose() override;
	void OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& Event);
	void ObGraphChanged(const FEdGraphEditAction& EditAction);
	

protected:
	void UpdateGraphFromAsset();
	void UpdateAssetFromGraph();

	private:
	UPROPERTY()
	UDialogTreeAsset* OpenedAsset = nullptr;
	UPROPERTY()
	UEdGraph* Graph = nullptr;	

	FDelegateHandle OnGraphChanged;
	//graph view
	TSharedPtr<SGraphEditor> ActiveGraphUI = nullptr;
	TSharedPtr<IDetailsView> SelectedNodeDetailView = nullptr;
};
