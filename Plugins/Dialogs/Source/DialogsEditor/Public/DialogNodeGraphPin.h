#pragma once
#include "SGraphPin.h"
#include "BlueprintGraphPanelPinFactory.h"

class SDialogNodeGraphPin : public SGraphPin
{

public:
	SLATE_BEGIN_ARGS(SDialogNodeGraphPin){}		
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments{}, InGraphPinObj);
	}

protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(0.2f, 1.0f, 0.2f, 1.f));
	}
};

struct FDialogNodePinFactory : public FGraphPanelPinFactory
{
	virtual ~FDialogNodePinFactory() {}
	virtual TSharedPtr<SGraphPin> CreatePin(class UEdGraphPin* Pin) const override
	{
		if (FName(TEXT("DialogNodePin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SDialogNodeGraphPin, Pin);
		}
		return nullptr;
	}	
};
