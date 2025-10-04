#include "DialogTreeEditorApp.h"

#include "DialogNode.h"
#include "DialogTreeEditorMode.h"
#include "DialogsRuntime/Public/DialogTreeAsset.h"
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
	OpenedAsset = Cast<UDialogTreeAsset>(InUObject);
	Graph = FBlueprintEditorUtils::CreateNewGraph(OpenedAsset, NAME_None, UEdGraph::StaticClass(), UDialogTreeGraphSchema::StaticClass());
	InitAssetEditor(Mode, InToolkitHost, TEXT("DialogTreeEditorApp"), FTabManager::FLayout::NullLayout,
		true, true, ObjectToEdit);

	AddApplicationMode(TEXT("DialogTreeEditorMode"), MakeShareable(new DialogTreeEditorMode(SharedThis(this))));
	SetCurrentMode(TEXT("DialogTreeEditorMode"));
	UpdateGraphFromAsset();
	OnGraphChanged = Graph->AddOnGraphChangedHandler( FOnGraphChanged::FDelegate::CreateSP(this, &DialogTreeEditorApp::ObGraphChanged));
}

void DialogTreeEditorApp::SetSelectedNodeDetailView(TSharedPtr<IDetailsView> InDetailsView)
{
	SelectedNodeDetailView = InDetailsView;
	SelectedNodeDetailView->OnFinishedChangingProperties().AddRaw(this,&DialogTreeEditorApp::OnNodeDetailViewPropertiesUpdated);
}

void DialogTreeEditorApp::OnGrapthSelectionChanged(const FGraphPanelSelectionSet& InSelection)
{
	//find first dialog node
	for (auto Object : InSelection)
	{
		if (UDialogNode* Node = Cast<UDialogNode>(Object))
		{
			SelectedNodeDetailView->SetObject(Node->GetDialogNodeInfo());
			return;
		}
	}
	SelectedNodeDetailView->SetObject(OpenedAsset);
}

void DialogTreeEditorApp::OnClose()
{
	UpdateAssetFromGraph();
	Graph->RemoveOnGraphChangedHandler(OnGraphChanged);
	FAssetEditorToolkit::OnClose();
}

void DialogTreeEditorApp::OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& Event)
{
	if (ActiveGraphUI)
	{
		ActiveGraphUI->NotifyGraphChanged();
	}
}

void DialogTreeEditorApp::ObGraphChanged(const FEdGraphEditAction& EditAction)
{
	UpdateAssetFromGraph();	
}

void DialogTreeEditorApp::UpdateGraphFromAsset()
{
	if (!OpenedAsset->Graph)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Graph"));
		return;
	}

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UEdGraphPin*> Pins;

	for (UDialogRuntimeNode* SourceNode : OpenedAsset->Graph->Nodes)
	{
		UDialogNode* NewNode = NewObject<UDialogNode>(Graph);
		NewNode->CreateNewGuid();
		NewNode->NodePosX = SourceNode->Location.X;
		NewNode->NodePosY = SourceNode->Location.Y;

		if (SourceNode->NodeInfo)
		{
			NewNode->SetDialogNodeInfo(DuplicateObject(SourceNode->NodeInfo, SourceNode));
		}
		else
		{
			NewNode->SetDialogNodeInfo(NewObject<UDialogNodeInfo>(SourceNode));
		}

		if (SourceNode->InputPin)
		{
			UDialogRuntimePin* Pin = SourceNode->InputPin;
			UEdGraphPin* UIPin = NewNode->CreateDialogNodePin(EGPD_Input, Pin->PinName);
			UIPin->PinId = Pin->PinID;
			if (Pin->Connection != nullptr)
			{
				Connections.Add(std::make_pair(Pin->PinID, Pin->Connection->PinID));				
			}
			Pins.Add(Pin->PinID, UIPin);
		}

		for (UDialogRuntimePin* Pin : SourceNode->OutputPins)
		{
			UEdGraphPin* UIPin = NewNode->CreateDialogNodePin(EGPD_Output, Pin->PinName);
			UIPin->PinId = Pin->PinID;

			if (Pin->Connection != nullptr)
			{
				Connections.Add(std::make_pair(Pin->PinID, Pin->Connection->PinID));
			}
			Pins.Add(Pin->PinID, UIPin);
		}
		Graph->AddNode(NewNode, true, true);
	}
	for (auto& Connection : Connections)
	{		
		UEdGraphPin* FromPin = *Pins.Find(Connection.first);
		UEdGraphPin* ToPin = *Pins.Find(Connection.second);
		FromPin->LinkedTo.Add(ToPin);
		ToPin->LinkedTo.Add(FromPin);
	}
}

void DialogTreeEditorApp::UpdateAssetFromGraph()
{
	if (!OpenedAsset || !Graph)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Graph or asset"));
		return;
	}
	UDialogRuntimeGraph* RuntimeGraph = NewObject<UDialogRuntimeGraph>(OpenedAsset);
	OpenedAsset->Graph = RuntimeGraph;

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UDialogRuntimePin*> Pins;
	for (UEdGraphNode* Node : Graph->Nodes)
	{

		UDialogNode* GraphNode = Cast<UDialogNode>(Node);
		if (!GraphNode) continue;
		
		UDialogRuntimeNode* RuntimeNode = NewObject<UDialogRuntimeNode>(RuntimeGraph);
		RuntimeNode->Location = FVector2D(Node->NodePosX, Node->NodePosY);
		RuntimeNode->NodeInfo = GraphNode->GetDialogNodeInfo();

		for (UEdGraphPin* Pin : Node->Pins)
		{
			UDialogRuntimePin* RuntimePin = NewObject<UDialogRuntimePin>(RuntimeNode);
			RuntimePin->PinName = Pin->PinName;
			RuntimePin->PinID = Pin->PinId;

			if (Pin->HasAnyConnections() && Pin->Direction == EGPD_Output)
			{
				//восстанавливаем только 1 пин, это надо доработать!
				std::pair<FGuid, FGuid> Connection = std::make_pair(Pin->PinId, Pin->LinkedTo[0]->PinId);
				Connections.Add(Connection);
			}
			Pins.Add(Pin->PinId, RuntimePin);
			if (Pin->Direction == EGPD_Input)
			{
				RuntimeNode->InputPin = RuntimePin;
			}
			else
			{
				RuntimeNode->OutputPins.Add(RuntimePin);
			}
		}
		RuntimeGraph->Nodes.Add(RuntimeNode);
	}

	for (auto& Connection : Connections)
	{
		UDialogRuntimePin* Pin1 = *Pins.Find(Connection.first);
		UDialogRuntimePin* Pin2 = *Pins.Find(Connection.second);
		Pin1->Connection = Pin2;
	}
}
