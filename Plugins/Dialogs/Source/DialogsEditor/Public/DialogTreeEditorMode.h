#pragma once
#include "CoreMinimal.h"
#include "DialogTreeEditorApp.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class DialogTreeEditorMode : public FApplicationMode
{
public:
	DialogTreeEditorMode(TSharedPtr<DialogTreeEditorApp> InApp);

	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;
	
private:
	TWeakPtr<DialogTreeEditorApp> App;
	FWorkflowAllowedTabSet Tabs;
};


