#pragma once

#include "Subsystems/WorldSubsystem.h"
#include "ImGuiDemoTickableWorldSubsystem.generated.h"

UCLASS()
class UImGuiDemoTickableWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:

	// FTickableGameObject implementation Begin
	virtual bool DoesSupportWorldType(EWorldType::Type WorldType) const override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickableWhenPaused() const override { return true; }
	virtual bool IsTickableInEditor() const override { return false; }
	virtual TStatId GetStatId() const override;
	// FTickableGameObject implementation End

	void ToggleShowDemo();

private:

	bool bShowDemo = false;
};
