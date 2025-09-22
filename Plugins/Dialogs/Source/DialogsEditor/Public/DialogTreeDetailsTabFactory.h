#pragma once

#pragma once
#include "CoreMinimal.h"
#include "DialogTreeEditorApp.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class DialogTreeDetailsTabFactory : public FWorkflowTabFactory
{
public:
	DialogTreeDetailsTabFactory(TSharedPtr<DialogTreeEditorApp> InApp);
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

private:
	TWeakPtr<DialogTreeEditorApp> App;
};
