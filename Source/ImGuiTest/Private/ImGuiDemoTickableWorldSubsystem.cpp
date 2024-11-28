#include "ImGuiDemoTickableWorldSubsystem.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "ImGuiConfig.h"
#include "imgui.h"


namespace
{
	void ToggleShowDemoFunc(const TArray<FString>& Args, UWorld* World)
	{
		if (UImGuiDemoTickableWorldSubsystem* SubSystem = World->GetSubsystem<UImGuiDemoTickableWorldSubsystem>())
		{
			SubSystem->ToggleShowDemo();
		}
	}

	FAutoConsoleCommandWithWorldAndArgs ToggleImGuiDemoCommand(
		TEXT("ImGui.ToggleDemo"),
		TEXT("Toggle showing the ImGui Demo window"),
		FConsoleCommandWithWorldAndArgsDelegate::CreateStatic(ToggleShowDemoFunc)
	);
}

bool UImGuiDemoTickableWorldSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer))
	{
		return false;
	}

	return !IsRunningDedicatedServer();
}

bool UImGuiDemoTickableWorldSubsystem::DoesSupportWorldType(EWorldType::Type WorldType) const
{
	// Not setup for editor use at this time
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

TStatId UImGuiDemoTickableWorldSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UImGuiDemoTickableWorldSubsystem, STATGROUP_Tickables);
}

void UImGuiDemoTickableWorldSubsystem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bShowDemo)
	{
		const ImGui::FScopedContext ScopedContext;
		if (ScopedContext)
		{
			ImGui::ShowDemoWindow();
		}
	}
}

void UImGuiDemoTickableWorldSubsystem::ToggleShowDemo()
{
	bShowDemo = !bShowDemo;

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (bShowDemo)
		{
			FInputModeGameAndUI InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
		else
		{
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = false;
		}
	}
}
